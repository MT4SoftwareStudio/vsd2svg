Name:           vsd2vg
Summary:        Convert VSD files into SVG files
Version:        0.0.3
Release:        0
License:        GPLv2+
Group:          Graphics
Url:            http://dia-installer.de/vsd2svg
Source:         vsd2svg-0.0.3.tar.xz
BuildRoot:      %{_tmppath}/%{name}-%{version}-buildroot
BuildRequires:  libvisio-devel >= 0.0.19
BuildRequires:  gcc, gcc-c++, pkg-config
BuildRequires:  libtool automake autoconf xz

%define prefix /usr

%description
vsd2svg is a tool to convert VSD files into SVG files.

Group:         Graphics 

%prep
rm -rf $RPM_BUILD_ROOT

%setup -q -n vsd2svg-%{version}


%build
CFLAGS=$RPM_OPT_FLAGS ./configure  --prefix=%{prefix} 
make %{?_smp_mflags}

%install
make prefix=$RPM_BUILD_ROOT%{prefix} install-strip

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%doc AUTHORS COPYING README
%{prefix}/bin/vsd2svg

%changelog
