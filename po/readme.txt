Use poedit (http://www.poedit.net) to translate application to new language.
wx-nfp.pot is a template file..

POT creation:

Linux:
cd  ..
ls src/*.cpp include/*.h > po/POTFILES.in
cd po
xgettext --c++ --add-location --no-wrap --escape --from-code=UTF-8 --force-po --keyword=_ --keyword=__ --keyword=wxPLURAL:1,2 --directory=.. -f POTFILES.in -o wx-nfp.pot

Win:
cd ..
dir /B src\*.cpp include\*.h > po\POTFILES.in
cd po
<path to xgettext>\xgettext.exe --c++ --add-location --no-wrap --escape --from-code=UTF-8 --force-po --keyword=_ --keyword=__ --keyword=wxPLURAL:1,2 --directory=.. -f POTFILES.in -o wx-nfp.pot


Next run poedit, select translation language file and from 'Catalog' select "Update from POT file" option.

