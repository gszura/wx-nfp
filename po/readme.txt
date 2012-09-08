Use poedit (http://www.poedit.net) to translate application to new language.
wx-nfp.pot is a template file..


POT creation:
dir /B src\*.cpp src\*.h > po\POTFILES.in
cd po
c:\apps\poedit\bin\xgettext.exe --c++ --add-location --no-wrap --escape --from-code=UTF-8 --force-po --keyword=_ --keyword=__ --keyword=wxPLURAL:1,2 --directory=.. -f POTFILES.in -o wx-nfp.pot

