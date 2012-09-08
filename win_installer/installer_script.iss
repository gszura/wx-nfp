[Languages]
Name: en; MessagesFile: compiler:Default.isl; LicenseFile: wx-nfp_licence_en.txt
Name: pl; MessagesFile: compiler:Languages\Polish.isl; LicenseFile: wx-nfp_licence_pl.txt

[Setup]
OutputBaseFilename=wx-nfp_setup_0.9.xxx
AppName=wx-nfp
AppVerName=wx-nfp 0.9
AppVersion=0.9
AppPublisher=Grzegorz Szura
AppPublisherURL=http://npr.szura.net/
DefaultDirName={pf}\wx-nfp
DefaultGroupName=wx-nfp
UninstallDisplayIcon={app}\wx-nfp.exe
ShowUndisplayableLanguages=true
Compression=lzma
SolidCompression=true
ChangesAssociations=true
AllowRootDirectory=true
AlwaysUsePersonalGroup=true
AlwaysShowDirOnReadyPage=true
AlwaysShowGroupOnReadyPage=true
SetupIconFile=..\data\icons\wx-nfp.ico


[Files]
Source: ..\wx-nfp_static.exe; DestDir: {app}; DestName: wx-nfp.exe
Source: ..\data\icons\wx-nfp.ico; DestDir: {app}
Source: ..\languages.cfg; DestDir: {app}
Source: ..\README; DestDir: {app}
Source: ..\doc\wx-nfp_changelog; DestDir: {app}\doc
Source: ..\doc\copyright; DestDir: {app}\doc
Source: ..\doc\html\index.html; DestDir: {app}\doc\html
Source: ..\doc\html\style.css; DestDir: {app}\doc\html
Source: ..\doc\html\en\index.html; DestDir: {app}\doc\html\en
Source: ..\doc\html\en\license-gnu.txt; DestDir: {app}\doc\html\en
Source: ..\doc\html\pl\index.html; DestDir: {app}\doc\html\pl
Source: ..\doc\html\pl\licencja-gnu.html; DestDir: {app}\doc\html\pl
Source: ..\doc\html\img\wx-nfp.ico; DestDir: {app}\doc\html\img
Source: ..\po\wx-nfp.pot; DestDir: {app}\po
Source: ..\po\readme.txt; DestDir: {app}\po
Source: ..\po\pl.mo; DestDir: {app}\po\pl; DestName: wx-nfp.mo


[Dirs]
Name: {app}\doc; Flags: uninsalwaysuninstall
Name: {app}\doc\html; Flags: uninsalwaysuninstall
Name: {app}\doc\html\en; Flags: uninsalwaysuninstall
Name: {app}\doc\html\pl; Flags: uninsalwaysuninstall
Name: {app}\doc\html\img; Flags: uninsalwaysuninstall
Name: {app}\po; Flags: uninsalwaysuninstall

[Icons]
Name: "{group}\wx-nfp"; Filename: "{app}\wx-nfp.exe"; WorkingDir: "{app}"; Comment: "Run wx-nfp application"; Languages: en
Name: "{group}\wx-nfp"; Filename: "{app}\wx-nfp.exe"; WorkingDir: "{app}"; Comment: "Uruchom aplikacje wx-nfp"; Languages: pl
Name: "{group}\Webpage"; Filename: "http://npr.szura.net/?l=en"; Comment: "Go to home page of the wx-nfp application"; Languages: en
Name: "{group}\Strona domowa"; Filename: "http://npr.szura.net/?l=pl"; Comment: "Otwórz strone domowa aplikacji wx-nfp"; Languages: pl
Name: "{group}\Uninstall wx-nfp"; Filename: "{uninstallexe}"; Comment: "Uninstall wx-nfp application"; Languages: en
Name: "{group}\Odinstaluj wx-nfp"; Filename: "{uninstallexe}"; Comment: "Odinstaluj aplikacje wx-nfp"; Languages: pl
Name: "{commondesktop}\wx-nfp"; Filename: "{app}\wx-nfp.exe"; WorkingDir: "{app}"; Comment: "Run wx-nfp application"; Tasks: desktopicon; Languages: en
Name: "{commondesktop}\wx-nfp"; Filename: "{app}\wx-nfp.exe"; WorkingDir: "{app}"; Comment: "Uruchom aplikacje wx-nfp"; Tasks: desktopicon; Languages: pl

[Run]

[Tasks]
Name: desktopicon; Description: Create a desktop icon; GroupDescription: Additional icons:; Languages: en
Name: desktopicon; Description: Utwórz skrót na pulpicie; GroupDescription: Dodatkowe skróty:; Languages: pl

[Registry]
Root: HKCR; Subkey: .nfpdata; Flags: createvalueifdoesntexist uninsdeletekey; Tasks: ; Languages: 
Root: HKCR; Subkey: .nfpdata\DefaultIcon; Flags: createvalueifdoesntexist uninsdeletekey; Tasks: ; Languages: ; ValueType: string; ValueData: {app}\wx-nfp.exe,0
Root: HKCR; Subkey: .nfpdata\shell; Flags: createvalueifdoesntexist uninsdeletekey; Tasks: ; Languages: 
Root: HKCR; Subkey: .nfpdata\shell\open; Flags: createvalueifdoesntexist uninsdeletekey; Tasks: ; Languages: 
Root: HKCR; Subkey: .nfpdata\shell\open\command; Flags: createvalueifdoesntexist uninsdeletekey; Tasks: ; Languages: ; ValueType: string; ValueData: """{app}\wx-nfp.exe"" ""%1"""

[InstallDelete]
Name: {app}\help; Type: filesandordirs
Name: {app}\language; Type: filesandordirs
Name: {app}\doc\changelog; Type: files
Name: {app}\changelog.txt; Type: files
Name: {app}\planned_versions.txt; Type: files
Name: {app}\release_notes.txt; Type: files
Name: {app}\wx-nfp_licence_en.txt; Type: files
Name: {app}\wx-nfp_licence_pl.txt; Type: files
