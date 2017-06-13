/*
Copyright (C) 2016  The AlterPCB team
Contact: Maarten Baert <maarten-baert@hotmail.com>

This file is part of AlterPCB.

AlterPCB is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

AlterPCB is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this AlterPCB.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "Basics.h"
#include "LinkedList.h"
#include "VData.h"

/*
The problem:
Shapes need to be flattened for rendering and some other actions. But flattening is potentially very slow, because the
hierarchy can be very complex and many components are generated by (slow) Python scripts. So we want to avoid this
as much as possible, and only re-flatten shapes when it is actually necessary.

The most common changes applied to shapes are:
- No action: The shape was not selected, so nothing changes.
- Select/unselect: This does not affect the shape data itself.
- Move/transform: This does affect the user-visible parameters, but should not require re-flattening.

The first two cases are solved by applying COW. The third one is more difficult. Possible strategies:
- Translate user-visible parameters into transform parameters and others. Only re-flatten when the other parameters are
  changed. This requires translation in both directions, which may introduce rounding errors.
- Lazy transforms: Add transform parameters on top of the regular parameters, and show the user the transformed parameters.
  If the user tries to change a parameter, then first replace the original parameters with the transformed ones, apply
  the change, and finally re-flatten the shape as usual. Transformed parameters can be generated on-demand.
- Fast OpenGL transforms during actions (for rendering), but the real transform is delayed until the action completes.
  This should make moves very fast, but doesn't help with anything else.

We use the second option. The parameters and flattened data is stored in ShapePrototype and deduplicated with COW.
The selection state and transform are added by ShapeInstance and deduplicated again with COW.
*/

class ShapePrototype;

struct ShapeTransform {
	real_t m_x, m_y, m_angle;
	bool m_mirror, m_flip;
	inline ShapeTransform() {}
	inline ShapeTransform(real_t x, real_t y, real_t angle, bool mirror, bool flip)
		: m_x(x), m_y(y), m_angle(angle), m_mirror(mirror), m_flip(flip) {}
};

class ShapeInstance : public LinkedListElement<ShapeInstance> {

private:
	Cow<ShapePrototype> m_shape_prototype;
	ShapeTransform m_transform;
	bool m_selected;

public:
	inline ShapeInstance(const Cow<ShapePrototype>& shape_prototype, bool selected)
		: m_shape_prototype(shape_prototype), m_transform(0.0, 0.0, 0.0, false, false), m_selected(selected) {}
	inline ShapeInstance(Cow<ShapePrototype>&& shape_prototype, bool selected)
		: m_shape_prototype(std::move(shape_prototype)), m_transform(0.0, 0.0, 0.0, false, false), m_selected(selected) {}
	inline ShapeInstance(const Cow<ShapePrototype>& shape_prototype, const ShapeTransform& transform, bool selected)
		: m_shape_prototype(shape_prototype), m_transform(transform), m_selected(selected) {}
	inline ShapeInstance(Cow<ShapePrototype>&& shape_prototype, const ShapeTransform& transform, bool selected)
		: m_shape_prototype(std::move(shape_prototype)), m_transform(transform), m_selected(selected) {}

	// noncopyable
	ShapeInstance(const ShapeInstance&) = delete;
	ShapeInstance& operator=(const ShapeInstance&) = delete;

	inline const ShapeTransform& GetTransform() const { return m_transform; }
	inline const Cow<ShapePrototype>& GetShapePrototype() const { return m_shape_prototype; }
	inline bool IsSelected() const { return m_selected; }

};
