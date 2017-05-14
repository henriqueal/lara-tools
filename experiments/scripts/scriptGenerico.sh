#!/bin/bash


declare -a arr_sel=("torneio" "roleta")
declare -a arr_gen=("100" "80" "50")
declare -a arr_pop=("300" "100" "80" "60" "40")
declare -a arr_cro=("90" "80" "70" "60")
declare -a arr_mut=("40" "30" "20" "10")
declare -a arr_sto=("20" "15" "10")

rm -rf /tmp/experiments
mkdir /tmp/experiments

for dir in /opt/lara-tools/benchmarks/TEXAS_42_LEON3/*/
do
  dir=${dir%*/}
	#mkdir "/tmp/teste/${dir##*/}/"
	mkdir "/tmp/experiments/${dir##*/}/"
	for sel in "${arr_sel[@]}"
	do
		for gen in "${arr_gen[@]}"
		do
			for pop in "${arr_pop[@]}"
			do
				for cro in "${arr_cro[@]}"
				do
					for mut in "${arr_mut[@]}"
					do

						larad -compiler=llvm371 -target=leon3 -algo=ga_henrique -nsteps=100 -seqlen=128 -nexec=1 ~/Benchmarks/TEXAS_42_LEON3/${dir##*/}/${dir##*/}.c > /tmp/experiments/${dir##*/}/${sel}_${gen}_${pop}_${cro}_${mut}
				  	
						$filename = "/tmp/experiments/${dir##*/}/${sel}_${gen}_${pop}_${cro}_${mut}"

				  	tail -n filename 30 > aux
				  	



				  done
				done
			done
		done
	done  
done