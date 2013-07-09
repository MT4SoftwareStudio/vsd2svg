Name:           vsd2svg
Summary:        Convert VSD files into SVG files
Version:        0.1.0
Release:        0
License:        GPLv2+
Group:          Graphics
Url:            http://dia-installer.de/vsd2svg
Source:         vsd2svg-0.1.0.tar.xz
BuildRoot:      %{_tmppath}/%{name}-%{version}-buildroot
BuildRequires:  libvisio-devel >= 0.0.19
BuildRequires:  gcc, gcc-c++, pkg-config
BuildRequires:  libtool automake autoconf xz
Prefix: %{prefix}

%description
vsd2svg is a tool to convert VSD files into SVG files.

Group:         Graphics 

%prep
%__rm -rf $RPM_BUILD_ROOT

%setup -q -n %{name}-%{version}

%build
%configure --prefix=%{_prefix} --libdir=%{_libdir}

%__make

%install
umask 022

%__make DESTDIR=$RPM_BUILD_ROOT install

%clean
%__rm -rf $RPM_BUILD_ROOT $RPM_BUILD_DIR/file.list.%{name}

%files
%defattr(644,root,root,755)
%doc README COPYING AUTHORS
%defattr(755,root,root,755)
%{_bindir}/vsd2svg*

%changelog
