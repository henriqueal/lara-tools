#!/bin/bash

#First experiment: One execution for this config for each TI code:
	#População inicial: 100 ;
	#Tamanho máximo do cromossomo:  128;
	#Tamanho máximo do cromossomo na população inicial 10;
	#Máximo de gerações: 100;
	#Taxa de crossover: 60%;
	#Taxa de mutação: 40%;
	#Critério de parada: número de gerações apenas.

#declare -a arr_sel=("torneio" "roleta")
#declare -a arr_gen=("100" "80" "50")
#declare -a arr_pop=("300" "100" "80" "60" "40")
#declare -a arr_cro=("90" "80" "70" "60")
#declare -a arr_mut=("40" "30" "20" "10")
#declare -a arr_sto=("20" "15" "10")
#declare -a arr_initChrom=("30" "50" "80" "100")



#rm -rf /tmp/experiments
#mkdir /tmp/experiments

for dir in /opt/lara-tools/benchmarks/TEXAS_42_LEON3/*/
#for dir in /tmp/here/*/
do
  dir=${dir%*/}

  for i in 1
  do
	  	#for init in "${arr_initChrom[@]}"
	  	#do
			#mkdir "/tmp/teste/${dir##*/}/"
			#mkdir "/tmp/experiments/${dir##*/}/"

			cd /tmp

			echo $dir
			#larad -compiler=llvm371 -target=leon3 -algo=ga_henrique -nsteps=100 -seqlen=128 -nexec=1 -popSize=2 ~/Benchmarks/TEXAS_42_LEON3/${dir##*/}/${dir##*/}.c > /tmp/experiments/${dir##*/}/${sel}_${gen}_${pop}_${cro}_${mut}
			larad -compiler=llvm371 -target=leon3 -algo=ga_henrique -nsteps=100 -seqlen=128 -nexec=1 -popSize=2 ~/Benchmarks/TEXAS_42_LEON3/${dir##*/}/${dir##*/}.c 
			
			#cd /tmp
			#larad -compiler=llvm371 -target=leon3 -algo=ga_henrique -selection=roulette -crossRate=80 -mutRate=20 -popSize=2 -maxGen=1 -seqlen=128 -nexec=1 -initChrom=128 ~/Benchmarks/TEXAS_42_LEON3/DSP_vecsumsq_c/DSP_vecsumsq_c.c
			#$filename = "/tmp/experiments/${dir##*/}/${sel}_${gen}_${pop}_${cro}_${mut}"
		#done
  done	
done
