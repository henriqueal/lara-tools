# Script de instalação do ambiente de compilação LARAD no linux Ubuntu 14.04
# ==========================================================================

# INSTALL SUPPORT PACKAGES
sudo apt-get update
sudo apt-get install lib32z1 #
sudo apt-get -y install timelimit
sudo apt-get -y install php5 #
sudo apt-get -y install openjdk-7-jre
sudo apt-get -y install libc6:i386 #
sudo apt-get -y install libncurses5:i386
sudo apt-get -y install libstdc++6:i386
sudo apt-get install g++-multilib #

# INSTALL LARAD
git clone 
#mkdir lara-tools
#unzip larad.zip -d ./lara-tools
#sudo mv lara-tools /opt
#echo 'export PATH=$PATH:/opt/lara-tools/larad/larac:/opt/lara-tools/larad/larai:/opt/lara-tools/larad/bin' >> ~/.bashrc
. ~/.bashrc 

# INSTALL CLANG
scp /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04.tar.xz root@138.197.110.151:/opt
tar xvf clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04.tar.xz 
sudo mv clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-14.04 /opt/clang+llvm-3.7.1-x86_64-linux-gnu-ubuntu-15.10

# INSTALL LEON3 BACKEND COMPILER
scp /opt/sparc-elf-4.4.2-1.0.45.tar.bz2 root@138.197.110.151:/opt
tar xvf sparc-elf-4.4.2-1.0.45.tar.bz2
sudo mv sparc-elf-4.4.2 /opt

# INSTALL LEON3 SIMULATOR
scp /opt/tsim-eval-2.0.49.tar.gz root@138.197.110.151:/opt
sudo tar xvf tsim-eval-2.0.49.tar.gz
sudo mv tsim-eval /opt/tsim2-leon3-eval

# INSTALL 42 BENCHMARKS FOR TI REPOSITORIES
mkdir Benchmarks
unzip TEXAS_42_LEON3.zip -d ./Benchmarks
sudo mv Benchmarks ~/

