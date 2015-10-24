Name:		capi-message-port
Summary:	Message Port managed library
Version: 	1.2.2.1
Release:    2
Group:		Application Framework/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
Source1001:	%{name}.manifest
BuildRequires:  cmake
BuildRequires:  pkgconfig(bundle)
BuildRequires:  pkgconfig(message-port)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(capi-base-common)

# runtime requires
Requires: message-port

Requires(post): /sbin/ldconfig
Requires(post): coreutils
Requires(postun): /sbin/ldconfig

Provides:   lib%{name}.so.1

%description
Message Port managed library

%package devel
Summary:  Message Port managed library (Development)
Group:    Application Framework/Development
Requires: %{name} = %{version}-%{release}

%description devel
Message Port managed library (DEV)

%prep
%setup -q
cp %{SOURCE1001} .

%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`

%if 0%{?sec_build_binary_debug_enable}
	CXXFLAGS="$CXXFLAGS -D_SECURE_LOG -DTIZEN_DEBUG_ENABLE"
%endif

%cmake . -DFULLVER=%{version} -DMAJORVER=${MAJORVER}

# Call make instruction with smp support
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license
install LICENSE.Apache-2.0 %{buildroot}/usr/share/license/%{name}

%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%{_libdir}/lib%{name}.so*
%manifest %{name}.manifest
/usr/share/license/%{name}

%files devel
%{_includedir}/appfw/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/lib%{name}.so
