#Sync SDL2
$sdl_url = 'https://www.libsdl.org/release/SDL2-devel-2.0.14-VC.zip'
$sdl_zip = './SDL2.zip'
$sdl_dest = '.'

Invoke-WebRequest -Uri $sdl_url -OutFile $sdl_zip
Expand-Archive -LiteralPath $sdl_zip -DestinationPath $sdl_dest

#Sync ANGLE
$env:DEPOT_TOOLS_WIN_TOOLCHAIN=0
git clone https://chromium.googlesource.com/angle/angle
Set-Location angle
python scripts/bootstrap.py
gclient sync
git checkout master

#Build ANGLE
gn gen out/Debug --args='target_cpu=\"x86\"'
autoninja -C out/Debug