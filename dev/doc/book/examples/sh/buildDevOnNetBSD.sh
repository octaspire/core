sudo pkgin install git
git clone git://github.com/octaspire/core
cd core
perl -pi -e 's/https/git/' .gitmodules
make submodules-init
make
