#!/bin/sh

# How to make test case
# 1. Modify PKG_NAME of "./config"
#		ex) PKG_NAME=capi-message-port
# 2. Add "./testcases/uts_{tc_name}.c"
#		ex) uts_message_port.c
# 3. Modify "./testcases/tclist"
#		ex) uts_message_port

# How to build test case
# 1. Run makespec.sh in "TC" directory
# 2. Build it
#		ex) gbs build -A armv7l --include-all ~/message-port/TC

# How to run test case
# 1. Install the tc packages
# 2. Run the test case with "run.sh" script
#		ex) sdb shell "cd /opt/home/capi-message-port && ./run.sh"
#			or
#		ex) sdb shell "cat \`cd /opt/home/capi-message-port && ./run.sh | grep -o '/opt.*journal'\`"

. ./config
if [ -z "$PKG_NAME" ]
then
	echo 'Cannot find the $PKG_NAME'
	exit 2
fi

git init
mkdir packaging
echo '%global __os_install_post %{nil}
%global __debug_install_post %{nil}
%global debug_package %{nil}

Name:		PKG_NAME-tc
Summary:	TC package
Version: 	1.2.2.1
Release:    1
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(PKG_NAME)

%description
TC package

%prep
%setup -q

%build
TC_ROOT=/var/tmp/dts_fw
rm -rf $TC_ROOT
mkdir $TC_ROOT
ln -s $PWD $TC_ROOT/TC
./build.sh
cat results/build-tar-result-*.journal
for SOURCE_FILE in `ls testcase/*.c`
do
	BIN_FILE=${SOURCE_FILE%%.c}
	if [ ! -f "$BIN_FILE" ]
	then
		exit 2
	fi
done
rm -rf $TC_ROOT

%install
mkdir -p %{buildroot}/opt/home/PKG_NAME
cp -rf . %{buildroot}/opt/home/PKG_NAME

%files
/opt/home/PKG_NAME/*' | sed "s#PKG_NAME#$PKG_NAME#g" > packaging/$PKG_NAME-tc.spec
