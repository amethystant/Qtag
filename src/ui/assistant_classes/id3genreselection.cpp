/*
 *    Qtag is an advanced but simple to use audio metadata editor. Runs on Linux
 *    and Windows. Supports many formats, including MPEG, Ogg Vorbis, Wave and FLAC
 *
 *    Copyright (C) 2015 - 2016  Karel Patlejch <kaja.patlejch@gmail.com>
 *
 *    Used libraries:
 *      TagLib - http://taglib.github.io/
 *      Qt - http://qt.io
 *
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License along
 *    with this program; if not, write to the Free Software Foundation, Inc.,
 *    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "ui/assistant_classes/id3genreselection.h"

Id3GenreSelection::Id3GenreSelection(QWidget* parent) : QComboBox(parent) {

    addItem("");
    addItem("Acid");
    addItem("Acid Jazz");
    addItem("Acid Punk");
    addItem("Alternative");
    addItem("AlternRock");
    addItem("Ambient");
    addItem("Bass");
    addItem("Blues");
    addItem("Cabaret");
    addItem("Christian Rap");
    addItem("Classic Rock");
    addItem("Classical");
    addItem("Comedy");
    addItem("Country");
    addItem("Cult");
    addItem("Dance");
    addItem("Darkwave");
    addItem("Death Metal");
    addItem("Disco");
    addItem("Dream");
    addItem("Electronic");
    addItem("Ethnic");
    addItem("Eurodance");
    addItem("Euro-Techno");
    addItem("Funk");
    addItem("Fusion");
    addItem("Game");
    addItem("Gangsta Rap");
    addItem("Gospel");
    addItem("Gothic");
    addItem("Grunge");
    addItem("Hard Rock");
    addItem("Hip-Hop");
    addItem("House");
    addItem("Industrial");
    addItem("Instrumental");
    addItem("Instrumental Pop");
    addItem("Instrumental Rock");
    addItem("Jazz");
    addItem("Jazz+Funk");
    addItem("Jungle");
    addItem("Lo-Fi");
    addItem("Metal");
    addItem("Meditative");
    addItem("Musical");
    addItem("Native American");
    addItem("New Age");
    addItem("New Wave");
    addItem("Noise");
    addItem("Oldies");
    addItem("Other");
    addItem("Polka");
    addItem("Pop");
    addItem("Pop-Folk");
    addItem("Pop / Funk");
    addItem("Pranks");
    addItem("Psychedelic");
    addItem("Punk");
    addItem("R&B");
    addItem("Rap");
    addItem("Rave");
    addItem("Reggae");
    addItem("Retro");
    addItem("Rock");
    addItem("Rock & Roll");
    addItem("Showtunes");
    addItem("Ska");
    addItem("Soul");
    addItem("Sound Clip");
    addItem("Soundtrack");
    addItem("Southern Rock");
    addItem("Space");
    addItem("Techno");
    addItem("Techno-Industrial");
    addItem("Top 40");
    addItem("Trailer");
    addItem("Trip-Hop");
    addItem("Trance");
    addItem("Tribal");
    addItem("Vocal");

}
