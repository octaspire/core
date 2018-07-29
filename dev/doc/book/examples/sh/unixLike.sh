curl -O octaspire.com/core.tar.bz2
curl -O https://octaspire.io/core.sha512
sha512sum -c core.sha512
tar jxf core.tar.bz2
cd core
sh how-to-build/YOUR_PLATFORM_NAME_HERE.XX
