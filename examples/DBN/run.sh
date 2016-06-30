#Parameters
#$1: number of layers

for i in {1..1}
do
    echo "Running iteration $i ..."
    #<optimization technique> <training set> <test set> <output results file name> <cross-validation iteration number> <model configuration file> <output best parameters file name> <n_epochs> <batch_size> <number of iterations for Constrastive Divergence> <1 - CD | 2 - PCD | 3 - FPCD> <number of DBM layers>
    #exemplo: ./run.sh 1 (It will run DBN with 1 layer)
    examples/bin/DropoutDBN examples/data/training_$i.dat examples/data/USPS_testing_16x16.dat USPS_PSO_$1L.txt $i examples/DBN/model_files/Dropout/PSO/pso_model_$1L.txt PSO_best_parameters_$i\_$1L.txt 10 20 1 1 $1 > PSO_convergence_$i\_$1L.txt
done