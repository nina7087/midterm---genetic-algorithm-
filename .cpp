#include <iostream>
#include <set>
#include <vector>

const int numPopulation = 50;
const int maxOrderMachine = numOrder/numMachine * 2;

int population[numPopulation][numMachine][maxOrderMachine];
int orderNumOfPopulation[numPopulation][numMachine];

void Generic()
{
    
    int count = 100;
    int num_of_evaluation = 10000;
    
    
    
    for( int i=0;i<100;++i )
    {
        
        
        for( int j=0;j<num_of_evaluation;++j ) {
            int evaluation_ratio = rand() % 100;
            if (evaluation_ratio < 20) {
                int individual_index = rand() % numPopulation;
                Mutation(population[individual_index], orderNumOfPopulation);
            } else {
                int individual_A_index = rand() % numPopulation;
                int individual_B_index = rand() % numPopulation;
                while (individual_A_index == individual_B_index) {
                    individual_B_index = rand() % numPopulation;
                }
                Copulation(individual_A[individual_A_index], individual_B[individual_B_index],  orderNumOfPopulation[individual_A_index], orderNumOfPopulation[individual_B_index]);
            }
        }
        
        //
    }
    
    
    
}

void Mutation(int individual[][maxOrderMachine], int orderNumOfPopulation[]) {
    int index_A = rand() % numMachine;
    int index_B = rand() % numMachine;
    while(index_A == index_B) {
        index_B = rand() % numMachine;
    }
    int index_oreder_in_A = rand() % orderNumOfPopulation[index_A];
    int index_oreder_in_B = rand() % orderNumOfPopulation[index_B];
    while(index_oreder_in_A == index_oreder_in_B) {
        index_oreder_in_B = rand() % orderNumOfPopulation[index_B];
    }
    int temp = individual[index_A][index_oreder_in_A];
    individual[index_A][index_oreder_in_A] = individual[index_B][index_oreder_in_B];
    individual[index_B][index_oreder_in_B] = temp;
    
}


void Legalize(int index_to_swap, int individual_A[][maxOrderMachine], int individual_B[][maxOrderMachine], set <int> original_individual_A_order, set <int> post_individual_A_order, int orderNumOfPopulation_A[], int orderNumOfPopulation_B[]) {
    
    set <int> overlap_in_A;
    for( int i=0;i<orderNumOfPopulation_A[index_to_swap];++i ) {
        if (original_individual_A_order.find(individual_A[index_to_swap][i]) == original_individual_A_order.end()) {
            overlap_in_A.insert(individual_A[index_to_swap][i]);
        }
    }
    
    for( int m=0;m<numMachine;++m ) {
        if (m != index_to_swap) {
            vector <int> temp_array;
            for( int j=0;j<orderNumOfPopulation_A[m];++j ) {
                if (overlap_in_A.find(individual_A[m][j]) == overlap_in_A.end()) {
                    temp_array.push_back(individual_A[m][j]);
                }
            }
            orderNumOfPopulation_A[m] = temp_array.size();
            for( int j=0;j<orderNumOfPopulation_A[m];++j ) {
                individual_A[m][j] = temp_array[j];
            }
        }
    }
    
    set <int> miss_in_A;
    for( int i=0;i<orderNumOfPopulation_B[index_to_swap];++i ) {
        if (post_individual_A_order.find(individual_B[index_to_swap][i]) == post_individual_A_order.end()) {
            miss_in_A.insert(individual_B[index_to_swap][i]);
        }
    }
    
    for( set <int>::iterator it = miss_in_A.begin();it!=miss_in_A.end();++it ) {
        int push_index = rand() % numMachine;
        while(index_to_swap == push_index) {
            push_index = rand() % numMachine;
        }
        individual_A[push_index][orderNumOfPopulation_A[push_index]++] = *it;
    }
    
}

void Copulation(int individual_A[][maxOrderMachine], int individual_B[][maxOrderMachine], int orderNumOfPopulation_A[], int orderNumOfPopulation_B[]) {
    
    int index_to_swap = rand() % numMachine;
    
    set <int> original_individual_A_order;
    set <int> original_individual_B_order;
    set <int> post_individual_A_order;
    set <int> post_individual_B_order;
    
    int temp_DNA[maxOrderMachine] = {0};
    int temp_orderNum = orderNumOfPopulation_A[index_to_swap];
    for( int i=0;i<orderNumOfPopulation_A[index_to_swap];++i ) {
        temp_DNA[i] = individual_A[index_to_swap][i];
        original_individual_A_order.insert(individual_A[index_to_swap][i]);
        post_individual_B_order.insert(individual_A[index_to_swap][i]);
    }
    for( int i=0;i<orderNumOfPopulation_B[index_to_swap];++i ) {
        individual_A[index_to_swap][i] = individual_B[index_to_swap][i];
        original_individual_B_order.insert(individual_B[index_to_swap][i]);
        post_individual_A_order.insert(individual_B[index_to_swap][i]);
    }
    orderNumOfPopulation_A[index_to_swap] = orderNumOfPopulation_B[index_to_swap];
    
    for( int i=0;i<temp_orderNum;++i ) {
        individual_B[index_to_swap][i] = temp_DNA[i];
    }
    orderNumOfPopulation_B[index_to_swap] = temp_orderNum;
    
    Legalize(index_to_swap, individual_A, individual_B, original_individual_A_order, post_individual_A_order,  orderNumOfPopulation_A, orderNumOfPopulation_B);
    Legalize(index_to_swap, individual_B, individual_A, original_individual_B_order, post_individual_B_order,  orderNumOfPopulation_B, orderNumOfPopulation_A);

}

