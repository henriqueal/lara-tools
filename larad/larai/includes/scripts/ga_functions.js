// =====================================================================================
// General Functions
// =====================================================================================

  // 1D Array initialization
  Array.init = function (dim, initValue) {
    var a = [], i;
    for (i = 0; i < dim; i++) {
      a[i] = initValue;
    }
    return a;
  };

  // Argument of object.sort() - extended version for minimization
  var by = function (name, minor) {
    return function (o, p) {
      var a, b;
      if (o && p && typeof o === 'object' && typeof p === 'object' ) {
        a = o[name];
        b = p[name];
        if (a === b) {
          return typeof minor === 'function' ? minor(o,p) : 0;
        }
        if (typeof a === typeof b) {
          return a < b ? -1 : 1;
        }
        return typeof a < typeof b ? -1 : 1;
      }
      else {
        throw {
          name: 'Error',
          message: 'Expected an object when sorting by ' + name
        };
      };
    };
  };

  // Argument of object.sort() - extended version for maximization
  var py = function (name, major) {
    return function (o, p) {
      var a, b;
      if (o && p && typeof o === 'object' && typeof p === 'object' ) {
        a = o[name];
        b = p[name];
        if (a === b) {
          return typeof major === 'function' ? major(o,p) : 0;
        }
        if (typeof a === typeof b) {
          return a > b ? -1 : 1;
        }
        return typeof a > typeof b ? -1 : 1;
      }
      else {
        throw {
          name: 'Error',
          message: 'Expected an object when sorting by ' + name
        };
      };
    };
  };

  // Specific optimization counter function
  var count = function (chromo, elem) {
    var counterElem = 0;
    var size = chromo.length;
    var idx;
    
    for (idx=0; idx < size; idx++) {
      if (chromo[idx] == elem) {
        counterElem++;
      };
    };
    
    return counterElem;
  };


  // Finder (interactive)
  var find = function (chromo, pos, elem) {
    var idx;
    var size = chromo.length;
    for (idx = pos; idx < size; idx++) {
      if (chromo[pos] == elem) {
        return (pos);
      };
    };
    return (-1);
  };

  // Write content in text file (write)
  function writeFile(path, content) {
      var file = new java.io.File(path);
      org.suikasoft.SharedLibrary.IoUtils.write(file,content);
  }

  // Write content in text file (append)
  function appendFile(path, content) {
      var file = new java.io.File(path);
      org.suikasoft.SharedLibrary.IoUtils.append(file,content);
  }
// =====================================================================================
// Specific Functions
// =====================================================================================

  // Individual maker
  var indiv_maker = function () {
    // Individual representation
    return {
      chromosome: [],
      chromosomeSize: 0,
      loopFactors: [],
      fitness: undefined
    };
  };

  // Individual copier
  var indiv_copy = function (source) {
    var sink = indiv_maker();
    sink.chromosome = source.chromosome.slice(0);
    sink.chromosomeSize = source.chromosomeSize;
    //sink.loopFactors = source.loopFactors.slice(0);
    sink.fitness = source.fitness;
    
    return sink;
  };

  // Individual finder
  var indiv_finder = function (base, indiv) {
    var size = base.length;
    var x;
    for (x=0; x < size; x++) {
      if (base[x].chromosome.join(",") == indiv.chromosome.join(","))
        return x;
    };
    
    return -1;
  };

  // Fitness finder
  var fitness_finder = function (base, indiv_fit) {
    var size = base.length;
    var x;
    for (x=0; x < size; x++) {
      if (base[x].fitness == indiv_fit)
        return x;
    };
    
    return -1;
  };

  var generateInitialPopulation = function(popSize, exploreParams, exploreParamSize, isnooptim, compile_execute_and_report, maxValue, total_steps, check_sequence_is_valid, maxwidth, initChrom){

    var vet_dist_prob = [];
    var population = [];
    var id;
    var gene; 
    var lengthChromossome;
    var sortChromossomeLength;
    var i;

    vet_dist_prob[0]=0;
    //generating chromosome probability by function: f(i)=i*10
    for (i=1; i<=maxwidth;i++){
      vet_dist_prob[i] = vet_dist_prob[i-1] + (i*10); 
    }

    for (id = 0; id < popSize; id++){

      population[id] = indiv_maker();
      //sortChromossomeLength = Math.floor(Math.random() * vet_dist_prob[exploreParamSize]);
      sortChromossomeLength = Math.floor(Math.random() * vet_dist_prob[maxwidth]);
      lengthChromossome =  1+(Math.floor(Math.random() * initChrom));
      /*
      for(i = 1; i <= maxwidth; i++){
        if(sortChromossomeLength <= vet_dist_prob[i]){
          lengthChromossome = i;
          break;
        }
      }*/
      
      for (gene=0; gene < lengthChromossome; gene++) {
        var pos = Math.floor(Math.random()*(exploreParamSize));
        //println("pos;gene: "+pos+";"+gene) 
        population[id].chromosome[gene] = exploreParams[pos];
      }
      
      // Apply code transformations and simulate
      optimLevel = population[id].chromosome.filter(isnooptim).join(" ");
      population[id].fitness = compile_execute_and_report(optimLevel);

      if(check_sequence_is_valid(population[id].fitness, optimLevel, population[id].chromosomeSize) == false) {
        population[id].fitness = Number.MAX_VALUE;
        population[id].chromosomeSize = maxwidth;
      }

      //antigamente tinha um check_sequence is valid
      population[id].chromosomeSize = population[id].chromosome.length;  
    }
    return population;
  };
  
  var tournment = function (individual, size, qty) {
    var i;
    var bestId = Math.floor(Math.random()*size);
    
    for (i = 1; i < qty; i++) {
      var idx = Math.floor(Math.random()*size);
      if (individual[idx].fitness < individual[bestId].fitness) {
        bestId  = idx;
      };
    };
    
    return bestId;
  };

  var roulette = function (population, size) {

    var roulette = [];
    var id=0;
    var random_number;
    var maxOfArray;

    roulette[0] = (population[0].fitness == Number.MAX_VALUE ? 0 : population[0].fitness);
    for(i=1; i< size; i++) {
      roulette[i] = roulette[i-1] + (population[i].fitness == Number.MAX_VALUE ? 0 : population[i].fitness);
      //println("roulette[" + i + "] =  " + roulette[i]);
    };

    maxOfArray = Math.max.apply(null, roulette);

    //println("maxOfArray: " + maxOfArray);

    roulette[0] = roulette[0] == 0 ? 1 : (maxOfArray + 1 - roulette[0] )
    for(i=1; i< size; i++) {
      roulette[i] = roulette[i-1] + (roulette[i] == 0 ? 1 : (maxOfArray + 1 - roulette[i] ) );
      //println("rouletteModificado[" + i + "] =  " + roulette[i]);
    };
    
    random_number = Math.random() * roulette[size - 1];
    while(random_number > roulette[id]){
      id++;
    };

    return (id);
  };

  var crossoverTwoPoints = function(population, parent1, parent2){
    var childrens = [];
    var point1 = Math.floor(Math.random()*population[parent1].chromosomeSize);
    var point2 = Math.floor(Math.random()*population[parent2].chromosomeSize);

    childrens[0] = indiv_maker();
    childrens[1] = indiv_maker();

    childrens[0].chromosome = population[parent1].chromosome.slice(0,point1).concat(population[parent2].chromosome.slice(point2));
    childrens[1].chromosome = population[parent2].chromosome.slice(0,point2).concat(population[parent1].chromosome.slice(point1));
    
    childrens[0].chromosomeSize = childrens[0].chromosome.length;
    childrens[1].chromosomeSize = childrens[1].chromosome.length;
/*
    println("###################################################################################################################");
    println("Points = ("+ point1 + ", "+point2+")");
    println("Fathers:\n");
    println(population[parent1].fitness + ";" + population[parent1].chromosomeSize + ";" 
      + population[parent1].chromosome.join(","));
    println("");
    println(population[parent2].fitness + ";" + population[parent2].chromosomeSize + ";" 
      + population[parent2].chromosome.join(","));
    
    println("Childrens:\n");
    println(childrens[0].fitness + ";" + childrens[0].chromosomeSize + ";" 
      + childrens[0].chromosome.join(","));
    println("");
    println(childrens[1].fitness + ";" + childrens[1].chromosomeSize + ";" 
      + childrens[1].chromosome.join(","));
*/
    return childrens;

  };

  var mutationX = function(individual, exploreParams, exploreParamSize){

    var qtyMutation = 4;
    var selectMutation = Math.ceil(Math.random()*qtyMutation);

    switch(selectMutation) {
    case 1:
        individual = mutation1(individual, exploreParams, exploreParamSize);
        break;
    case 2:
        individual = mutation2(individual);
        break;
    case 3:
        individual = mutation3(individual);
        break;
    case 4:
        individual = mutation4(individual, exploreParams, exploreParamSize);
        break;
    }
    
    return individual;

  };

  var mutation1 = function(individual, exploreParams, exploreParamSize, isnooptim, compile_execute_and_report){
    //Inclusão de um novo passo de otimização
    var sortedIndex = Math.floor(Math.random()*individual.chromosomeSize+1); //+1eh que posso adicionar no fim...
    var sortedOptimizations = Math.floor(Math.random()*exploreParamSize); //sort an optimization

    //println(individual.fitness + ";" + individual.chromosomeSize + ";" + individual.chromosome.join(","));
    individual.chromosome.splice(sortedIndex, 0, exploreParams[sortedOptimizations]);
    individual.chromosomeSize++;
    
    //println(individual.fitness + ";" + individual.chromosomeSize + ";" + individual.chromosome.join(","));
    //println("---------------------------------------------------------------------------------------------------");
    return individual;
  };

  var mutation2 = function(individual, isnooptim, compile_execute_and_report){
    //Remocao de um passo de otimização
    var sortedIndex = Math.floor(Math.random()*individual.chromosomeSize);

    //println("index: "+ sortedIndex);

    //println(individual.fitness + ";" + individual.chromosomeSize + ";" + individual.chromosome.join(","));
    individual.chromosome.splice(sortedIndex, 1);
    individual.chromosomeSize--;

    //println(individual.fitness + ";" + individual.chromosomeSize + ";" + individual.chromosome.join(","));
    //println("---------------------------------------------------------------------------------------------------");
    return individual;
  };

  var mutation3 = function(individual, isnooptim, compile_execute_and_report){
    //Cross two random genes

    var sortedIndex1 = Math.floor(Math.random()*individual.chromosomeSize);
    var sortedIndex2 = Math.floor(Math.random()*individual.chromosomeSize);

    //println("index1: "+ sortedIndex1 + "; index2: "+ sortedIndex2);

    //println(individual.fitness + ";" + individual.chromosomeSize + ";" + individual.chromosome.join(","));

    var aux = individual.chromosome[sortedIndex1];
    individual.chromosome[sortedIndex1] = individual.chromosome[sortedIndex2];
    individual.chromosome[sortedIndex2] = aux;
   
    //println(individual.fitness + ";" + individual.chromosomeSize + ";" + individual.chromosome.join(","));
    //println("---------------------------------------------------------------------------------------------------");

    return individual;
  };

  var mutation4 = function(individual, exploreParams, exploreParamSize, isnooptim, compile_execute_and_report){
    //Select on gene and replace by another of exploreParams...

    var sortedIndex = Math.floor(Math.random()*individual.chromosomeSize+1); //+1eh que posso adicionar no fim...
    var sortedOptimizations = Math.floor(Math.random()*exploreParamSize); //sort an optimization

    //println("sortedIndex: "+ sortedIndex + "sortedOptimizations: "+ exploreParams[sortedOptimizations]);

    //println(individual.fitness + ";" + individual.chromosomeSize + ";" + individual.chromosome.join(","));
    individual.chromosome.splice(sortedIndex, 1, exploreParams[sortedOptimizations]);
    
    //println(individual.fitness + ";" + individual.chromosomeSize + ";" + individual.chromosome.join(","));
    //println("---------------------------------------------------------------------------------------------------");
    return individual;
  };