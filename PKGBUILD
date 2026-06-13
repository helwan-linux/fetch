# Maintainer: Saeed Badreldin <https://github.com/helwan-linux>
# Project: Helwan Linux System Fetch Tool 

pkgname=helfetch
pkgver=1.0.3
pkgrel=3
pkgdesc="A high-performance system information tool written in C and x86_64 Assembly for Helwan Linux "
arch=('x86_64')
url="https://github.com/helwan-linux/fetch" 
license=('GPL3')
depends=('glibc')
makedepends=('gcc' 'nasm' 'make' 'git')
source=("${pkgname}::git+${url}.git") 
sha256sums=('SKIP')

build() {
    # البحث عن المجلد الذي يحتوي على الـ Makefile الفعلي
    # أحياناً يكون الكود داخل مجلد فرعي باسم fetch أو src
    local makefile_dir=$(find "${srcdir}/${pkgname}" -name "Makefile" -exec dirname {} + | head -n 1)
    
    if [ -z "$makefile_dir" ]; then
        echo "ERROR: Makefile not found in the repository!"
        exit 1
    fi

    cd "$makefile_dir"
    echo "Found Makefile in: $makefile_dir"
    
    # البناء باستخدام الماك فايل المتاح
    make clean || true
    make
}

package() {
    # البحث عن الملف التنفيذي الناتج (helfetch)
    local binary_path=$(find "${srcdir}/${pkgname}" -name "helfetch" -type f -executable | head -n 1)
    
    if [ -z "$binary_path" ]; then
        echo "ERROR: Binary 'helfetch' not found after build!"
        exit 1
    fi

    # تثبيت الملف التنفيذي في مسار النظام
    install -Dm755 "$binary_path" "${pkgdir}/usr/bin/helfetch"
}
