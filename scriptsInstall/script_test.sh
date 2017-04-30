# Script de teste do ambiente de compilação LARAD no linux Ubuntu 14.04
# ==========================================================================
#Adapted by Henrique Lima (18/04/2017)

#Verificando o diretorio /opt
Após a instalação este diretório deve conter:
  -lara-tools
  -tsim (expira rapidamente. Deve baixar do próprio site as novas versões)
  -sparc
  -clang

# LARAD
larad

# LEON3 SIMULATOR
#/opt/tsim2-leon3-eval/tsim/linux-x64/tsim-leon3 # Se ocorreu tudo bem, dar quit para sair
/opt/tsim-eval/tsim/linux-x64/tsim-leon3

# LEON3 BACKEND COMPILER
/opt/sparc-elf-4.4.2/bin/sparc-elf-gcc ~/Benchmarks/TEXAS_42_LEON3/DSP_maxval_c/DSP_maxval_c.c ~/Benchmarks/TEXAS_42_LEON3/DSP_maxval_c/DSP_maxval_c_main.c

# LLVM COMPILER: CLANG (FRONTEND) + OPT
/opt/lara-tools/larad/targets/leon3/llvm371/scripts/test.sh /home/henrique/Benchmarks/TEXAS_42_LEON3/DSP_autocor_c/DSP_autocor_c.c

# DSE
#larad -compiler=llvm371 -target=leon3 -algo=sa -nsteps=100 -seqlen=128 -nexec=1 ~/Benchmarks/TEXAS_42_LEON3/DSP_autocor_c/DSP_autocor_c.c
cd /tmp; larad -compiler=llvm371 -target=leon3 -algo=ga_henrique -nsteps=100 -seqlen=128 -nexec=1 ~/Benchmarks/TEXAS_42_LEON3/DSP_autocor_c/DSP_autocor_c.c
