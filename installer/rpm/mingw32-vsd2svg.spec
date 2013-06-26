%define __strip %{_mingw32_strip}
%define __objdump %{_mingw32_objdump}
%define _use_internal_dependency_generator 0
%define __find_requires %{_mingw32_findrequires}
%define __find_provides %{_mingw32_findprovides}
%define __os_install_post %{_mingw32_debug_install_post} \
                          %{_mingw32_install_post}

Name:           mingw32-vsd2vg
Summary:        Convert VSD files into SVG files
Version:        0.1.0
Release:        0
License:        GPLv2+
Group:          Graphics
Url:            http://dia-installer.de/vsd2svg
Source:         vsd2svg-%{version}.tar.xz
BuildRoot:      %{_tmppath}/%{name}-%{version}-buildroot
BuildRequires:  mingw32-libvisio-devel >= 0.0.28
BuildRequires:  mingw32-cross-gcc, mingw32-cross-gcc-c++, mingw32-cross-pkg-config
BuildRequires:  libtool automake autoconf xz

BuildArch:      noarch
#!BuildIgnore: post-build-checks  

%description
vsd2svg is a tool to convert SVG files into SVG files.

%package tools
Summary:        Tools to work with documents in MS Visio file-format
Group:          System/Libraries

%description tools
A tools to convert VSD files into SVG files.

%{_mingw32_debug_package}

%prep
rm -rf $RPM_BUILD_ROOT

%setup -q -n vsd2svg-%{version}


%build
#echo "lt_cv_deplibs_check_method='pass_all'" >>%{_mingw32_cache}
%{_mingw32_configure} \
	--enable-shared --disable-static \
	--without-docs --disable-werror

%{_mingw32_make} %{?_smp_mflags} || %{_mingw32_make}

%install
%{_mingw32_make} DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)

%files tools
%defattr(-,root,root)
%{_mingw32_bindir}/vsd2*.exe

%changelog
