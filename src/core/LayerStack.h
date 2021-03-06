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
#include "Qt.h"
#include "StringRegistry.h"
#include "TrackingPointer.h"

enum LAYERTEXTURE{
	LAYERTEXTURE_SOLID,
	LAYERTEXTURE_VSTRIPE_LIGHT,
};

enum LAYERTYPE{
	LAYERTYPE_METAL,
	LAYERTYPE_SILK,
	LAYERTYPE_SOLDERMASK,
	LAYERTYPE_VIA,
};

struct LogicalLayer{
	stringtag_t m_name;
	QColor m_color;
	LAYERTEXTURE m_texture;

	inline LogicalLayer(stringtag_t name, QColor color, LAYERTEXTURE texture)
		: m_name(name), m_color(color), m_texture(texture) {}
};

class LayerStack : public TrackingTarget<LayerStack> {

private:
	stringtag_t m_name;
	std::vector<LogicalLayer> m_logical_layers;

public:
	LayerStack(stringtag_t name);

	// noncopyable
	LayerStack(const LayerStack&) = delete;
	LayerStack& operator=(const LayerStack&) = delete;

	inline stringtag_t GetName() const { return m_name; }
	std::vector<std::string> GetLayerNames();
	inline size_t GetLogicalLayerSize() const { return m_logical_layers.size(); }
	inline LogicalLayer* GetLogicalLayer(size_t index) { return &m_logical_layers[index]; }

	void AddLayer(LogicalLayer logical_layer);
};


