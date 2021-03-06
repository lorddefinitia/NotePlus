// This file is part of Notepad++ project
// Copyright (C)2003 Don HO <don.h@free.fr>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// Note that the GPL places important restrictions on "derived works", yet
// it does not provide a detailed definition of that term.  To avoid      
// misunderstandings, we consider an application to constitute a          
// "derivative work" for the purpose of this license if it does any of the
// following:                                                             
// 1. Integrates source code from Notepad++.
// 2. Integrates/includes/aggregates Notepad++ into a proprietary executable
//    installer, such as those produced by InstallShield.
// 3. Links to a library or executes a program that does any of the above.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#ifndef LOCALIZATIONSTRING_H
#define LOCALIZATIONSTRING_H
LocalizationSwitcher::LocalizationDefinition localizationDefs[] = {
	{TEXT("English"), TEXT("english.xml")},
	{TEXT("English (customizable)"), TEXT("english_customizable.xml")},
	{TEXT("Français"), TEXT("french.xml")},
	{TEXT("中文繁體"), TEXT("chinese.xml")},
	{TEXT("中文简体"), TEXT("chineseSimplified.xml")},
	{TEXT("한국어"), TEXT("korean.xml")},
	{TEXT("日本語"), TEXT("japanese.xml")},
	{TEXT("Deutsch"), TEXT("german.xml")},
	{TEXT("Español"), TEXT("spanish.xml")},
	{TEXT("Italiano"), TEXT("italian.xml")},
	{TEXT("Português"), TEXT("portuguese.xml")},
	{TEXT("Português brasileiro"), TEXT("brazilian_portuguese.xml")},
	{TEXT("Nederlands"), TEXT("dutch.xml")},
	{TEXT("Русский"), TEXT("russian.xml")},
	{TEXT("Polski"), TEXT("polish.xml")},
	{TEXT("Català"), TEXT("catalan.xml")},
	{TEXT("Česky"), TEXT("czech.xml")},
	{TEXT("Magyar"), TEXT("hungarian.xml")},
	{TEXT("Română"), TEXT("romanian.xml")},
	{TEXT("Türkçe"), TEXT("turkish.xml")},
	{TEXT("فارسی"), TEXT("farsi.xml")},
	{TEXT("Українська"), TEXT("ukrainian.xml")},
	{TEXT("עברית"), TEXT("hebrew.xml")},
	{TEXT("Nynorsk"), TEXT("nynorsk.xml")},
	{TEXT("Norsk"), TEXT("norwegian.xml")},
	{TEXT("Occitan"), TEXT("occitan.xml")},
	{TEXT("ไทย"), TEXT("thai.xml")},
	{TEXT("Furlan"), TEXT("friulian.xml")},
	{TEXT("الْعَرَبيّة"), TEXT("arabic.xml")},
	{TEXT("Suomi"), TEXT("finnish.xml")},
	{TEXT("Lietuvių"), TEXT("lithuanian.xml")},
	{TEXT("Ελληνικά"), TEXT("greek.xml")},
	{TEXT("Svenska"), TEXT("swedish.xml")},
	{TEXT("Galego"), TEXT("galician.xml")},
	{TEXT("Slovenščina"), TEXT("slovenian.xml")},
	{TEXT("Slovenčina"), TEXT("slovak.xml")},
	{TEXT("Dansk"), TEXT("danish.xml")},
	{TEXT("Estremeñu"), TEXT("extremaduran.xml")},
	{TEXT("Žemaitiu ruoda"), TEXT("samogitian.xml")},
	{TEXT("Български"), TEXT("bulgarian.xml")},
	{TEXT("Bahasa Indonesia"), TEXT("indonesian.xml")},
	{TEXT("Gjuha shqipe"), TEXT("albanian.xml")},
	{TEXT("Hrvatski jezik"), TEXT("croatian.xml")},
	{TEXT("ქართული ენა"), TEXT("georgian.xml")},
	{TEXT("Euskara"), TEXT("basque.xml")},
	{TEXT("Español argentina"), TEXT("spanish_ar.xml")},
	{TEXT("Беларуская мова"), TEXT("belarusian.xml")},
	{TEXT("Srpski"), TEXT("serbian.xml")},
	{TEXT("Cрпски"), TEXT("serbianCyrillic.xml")},
	{TEXT("Bahasa Melayu"), TEXT("malay.xml")},
	{TEXT("Lëtzebuergesch"), TEXT("luxembourgish.xml")},
	{TEXT("Tagalog"), TEXT("tagalog.xml")},
	{TEXT("Afrikaans"), TEXT("afrikaans.xml")},
	{TEXT("Қазақша"), TEXT("kazakh.xml")},
	{TEXT("O‘zbekcha"), TEXT("uzbek.xml")},
	{TEXT("Ўзбекча"), TEXT("uzbekCyrillic.xml")},
	{TEXT("䬄䀄㌄䬄㜄 䈀㠄㬄㠄∄⤀Ⰰ 吀䔀堀吀⠀∀欀礀爀最礀稀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀ᰀ〄㨄㔄㐄㸄㴄䄄㨄㠄 堀〄㜄㠄㨄∄⤀Ⰰ 吀䔀堀吀⠀∀洀愀挀攀搀漀渀椀愀渀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀氀愀琀瘀椀攀愀甁 瘀愀氀漀搀愀∀⤀Ⰰ 吀䔀堀吀⠀∀氀愀琀瘀椀愀渀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀ꐀ긋뼋됋촋∋⤀Ⰰ 吀䔀堀吀⠀∀琀愀洀椀氀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀䄀稀夀爂戀愀礀挀愀渀 搀椀氀椀∀⤀Ⰰ 吀䔀堀吀⠀∀愀稀攀爀戀愀椀樀愀渀椀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀䈀漀猀愀渀猀欀椀∀⤀Ⰰ 吀䔀堀吀⠀∀戀漀猀渀椀愀渀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀䔀猀瀀攀爀愀渀琀漀∀⤀Ⰰ 吀䔀堀吀⠀∀攀猀瀀攀爀愀渀琀漀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀娀攀渀攀椀稀攀∀⤀Ⰰ 吀䔀堀吀⠀∀氀椀最甀爀椀愀渀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀㤀㼉⠉䴉☉䀉∉⤀Ⰰ 吀䔀堀吀⠀∀栀椀渀搀椀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀匀愀爀搀甀∀⤀Ⰰ 吀䔀堀吀⠀∀猀愀爀搀椀渀椀愀渀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀☀윆䨆㨆윆ㄆ蘆픆∆⤀Ⰰ 吀䔀堀吀⠀∀甀礀最栀甀爀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀␀䘌㈌䄌ᜌ䄌∌⤀Ⰰ 吀䔀堀吀⠀∀琀攀氀甀最甀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀愀爀愀最漀渀猀∀⤀Ⰰ 吀䔀堀吀⠀∀愀爀愀最漀渀攀猀攀⸀砀洀氀∀⤀紀Ⰰഀ਀ऀ笀吀䔀堀吀⠀∀가븉舉눉븉∉⤀Ⰰ 吀䔀堀吀⠀∀戀攀渀最愀氀椀⸀砀洀氀∀⤀紀ഀ਀紀㬀ഀ਀⌀攀渀搀椀昀 䰀伀䌀䄀䰀䤀娀䄀吀䤀伀一匀吀刀䤀一䜀开䠀ഀ਀਀