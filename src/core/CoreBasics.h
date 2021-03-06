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

enum LibraryType {
	LIBRARYTYPE_JSON,
	LIBRARYTYPE_PYTHON,
};

enum DrawingType {
	DRAWINGTYPE_SCHEMATIC,
	DRAWINGTYPE_SYMBOL,
	DRAWINGTYPE_LAYOUT,
};

/*enum ShapeType {
	SHAPETYPE_UNDEFINED,
	SHAPETYPE_PRIMITIVE,
	SHAPETYPE_JSON,
	SHAPETYPE_PYTHON,
};*/

enum LibraryTreeItemType {
	LIBRARYTREEITEMTYPE_LIBRARY,
	LIBRARYTREEITEMTYPE_DRAWING,
};

enum DropLocation {
	DROPLOCATION_BEFORE,
	DROPLOCATION_ON_BEFORE,
	DROPLOCATION_ON_AFTER,
	DROPLOCATION_AFTER,
};

