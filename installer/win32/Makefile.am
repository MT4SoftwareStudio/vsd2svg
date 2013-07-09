EXTRA_DIST = vsd2svg-setup.nsi vsd2svg_homepage.url

icu_version = 51.1-2.54
libgcc_version = 4.8.1-2.23
libstdcpp_version = 4.8.1-2.23
libvisio_version = 0.0.29-1.5
libwpg_version = 0.2.2-1.33
libwpd_version = 0.9.8-1.19
libxml_version = 2.9.0-2.51
vsd2svg_version = 0.1.0-12.1
zlib_version = 1.2.7-1.207
setup:
	-rm -Rf mingw32*
	-rm -Rf usr
	wget http://download.opensuse.org/repositories/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-libvisio-$(libvisio_version).noarch.rpm
	7z x mingw32-libvisio-$(libvisio_version).noarch.rpm
	7z x  mingw32-libvisio-$(libvisio_version).noarch.cpio.lzma
	7z x  mingw32-libvisio-$(libvisio_version).noarch.cpio
	wget http://download.opensuse.org/repositories/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-libwpg-$(libwpg_version).noarch.rpm
	7z x mingw32-libwpg-$(libwpg_version).noarch.rpm
	7z x mingw32-libwpg-$(libwpg_version).noarch.cpio.lzma
	7z x mingw32-libwpg-$(libwpg_version).noarch.cpio
	wget http://download.opensuse.org/repositories/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-libwpd-$(libwpd_version).noarch.rpm
	7z x mingw32-libwpd-$(libwpd_version).noarch.rpm
	7z x mingw32-libwpd-$(libwpd_version).noarch.cpio.lzma
	7z x mingw32-libwpd-$(libwpd_version).noarch.cpio
	wget http://download.opensuse.org/repositories/home:/sdteffen_de:/branches:/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-vsd2svg-tools-$(vsd2svg_version).noarch.rpm
	7z x mingw32-vsd2svg-tools-$(vsd2svg_version).noarch.rpm
	7z x mingw32-vsd2svg-tools-$(vsd2svg_version).noarch.cpio.lzma
	7z x mingw32-vsd2svg-tools-$(vsd2svg_version).noarch.cpio
	wget http://download.opensuse.org/repositories/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-libicu-$(icu_version).noarch.rpm
	7z x mingw32-libicu-$(icu_version).noarch.rpm
	7z x mingw32-libicu-$(icu_version).noarch.cpio.lzma
	7z x mingw32-libicu-$(icu_version).noarch.cpio
	wget http://download.opensuse.org/repositories/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-libxml2-$(libxml_version).noarch.rpm
	7z x mingw32-libxml2-$(libxml_version).noarch.rpm
	7z x mingw32-libxml2-$(libxml_version).noarch.cpio.lzma
	7z x mingw32-libxml2-$(libxml_version).noarch.cpio
	wget http://download.opensuse.org/repositories/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-zlib-$(zlib_version).noarch.rpm
	7z x mingw32-zlib-$(zlib_version).noarch.rpm
	7z x mingw32-zlib-$(zlib_version).noarch.cpio.lzma
	7z x mingw32-zlib-$(zlib_version).noarch.cpio
	wget http://download.opensuse.org/repositories/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-libstdc++-$(libstdcpp_version).noarch.rpm
	7z x "mingw32-libstdc++-$(libstdcpp_version).noarch.rpm"
	7z x "mingw32-libstdc++-$(libstdcpp_version).noarch.cpio.lzma"
	7z x "mingw32-libstdc++-$(libstdcpp_version).noarch.cpio"
	wget http://download.opensuse.org/repositories/windows:/mingw:/win32/openSUSE_Factory/noarch/mingw32-libgcc-$(libgcc_version).noarch.rpm
	7z x mingw32-libgcc-$(libgcc_version).noarch.rpm
	7z x mingw32-libgcc-$(libgcc_version).noarch.cpio.lzma
	7z x mingw32-libgcc-$(libgcc_version).noarch.cpio
	cp usr/i686-w64-mingw32/sys-root/mingw/bin/* .
	makensis vsd2svg-setup.nsi