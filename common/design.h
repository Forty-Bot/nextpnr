/*
 *  nextpnr -- Next Generation Place and Route
 *
 *  Copyright (C) 2018  Clifford Wolf <clifford@clifford.at>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef DESIGN_H
#define DESIGN_H

#include <stdint.h>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>

// replace with proper IdString later
typedef std::string IdString;

// replace with haslib later
template<typename T> using pool = std::unordered_set<T>;
template<typename T, typename U> using dict = std::unordered_map<T, U>;
using std::vector;

struct GraphicElement
{
	enum {
		G_LINE,
		G_BOX,
		G_CIRCLE,
		G_LABEL
	} type;

	float x1, y1, x2, y2, z;
	std::string text;
};

#include "chip.h"

struct CellInfo;

struct PortRef
{
	CellInfo *cell;
	IdString port;
};

struct NetInfo
{
	IdString name;
	PortRef driver;
	vector<PortRef> users;
	dict<IdString, std::string> attrs;

	// wire -> (uphill_wire, delay)
	dict<WireId, std::pair<WireId, DelayInfo>> wires;
};

enum PortType
{
	PORT_IN = 0,
	PORT_OUT = 1,
	PORT_INOUT = 2
};

struct PortInfo
{
	IdString name;
	NetInfo *net;
	PortType type;
};

struct CellInfo
{
	IdString name, type;
	dict<IdString, PortInfo> ports;
	dict<IdString, std::string> attrs, params;

	BelId bel;
	// cell_port -> bel_pin
	dict<IdString, IdString> pins;
};

struct Design
{
	struct Chip chip;

	Design(ChipArgs args) : chip(args) {
		// ...
	}

	dict<IdString, NetInfo*> nets;
	dict<IdString, CellInfo*> cells;
};

#endif
