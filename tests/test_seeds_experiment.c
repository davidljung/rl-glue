/* 
* Copyright (C) 2007, Brian Tanner

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.

* 
*  $Revision$
*  $Date$
*  $Author$
*  $HeadURL$
* 
*/


#include <stdio.h>

#include <rlglue/Experiment_common.h>
#include <string.h>

#include <useful_functions.h>

	int tests_failed=0;
	int test_count=0;

	void check_fail(int condition){
		test_count++;
		if(condition!=0){
			printf("Failed check: %d\n",test_count);
			tests_failed++;
		}
	}

	

int main(int argc, char *argv[]) {
	state_key_t the_state_key={0};
	random_seed_key_t the_random_seed={0};
	
	state_key_t returned_state_key;
	random_seed_key_t returned_random_seed_key;
	
	clean_abstract_type(&the_state_key);
	clean_abstract_type(&the_random_seed);
	
	set_k_ints_in_abstract_type(&the_state_key,3);
	set_k_doubles_in_abstract_type(&the_state_key,7);
	set_k_chars_in_abstract_type(&the_state_key,2);

	set_k_ints_in_abstract_type(&the_random_seed,1);
	set_k_doubles_in_abstract_type(&the_random_seed,2);
	set_k_chars_in_abstract_type(&the_random_seed,4);
	
	/*	compare_abstract_types */
	
	RL_init();
	
	RL_set_state(the_state_key);
	returned_state_key=RL_get_state();
	check_fail(compare_abstract_types(&the_state_key,&returned_state_key)!=0);

	RL_set_random_seed(the_random_seed);
	returned_random_seed_key=RL_get_random_seed();
	check_fail(compare_abstract_types(&the_random_seed,&returned_random_seed_key)!=0);
	
	
	set_k_ints_in_abstract_type(&the_state_key,0);
	set_k_doubles_in_abstract_type(&the_state_key,0);
	set_k_chars_in_abstract_type(&the_state_key,0);
	
	set_k_ints_in_abstract_type(&the_random_seed,0);
	set_k_doubles_in_abstract_type(&the_random_seed,0);
	set_k_chars_in_abstract_type(&the_random_seed,0);

	RL_set_state(the_state_key);
	returned_state_key=RL_get_state();
	check_fail(compare_abstract_types(&the_state_key,&returned_state_key)!=0);

	RL_set_random_seed(the_random_seed);
	returned_random_seed_key=RL_get_random_seed();
	check_fail(compare_abstract_types(&the_random_seed,&returned_random_seed_key)!=0);
	
	if(tests_failed!=0)
		printf("Failed %d / %d checks in %s\n",tests_failed,test_count, __FILE__);
	else
		printf("Passed all %d checks in %s\n",test_count,__FILE__);
	return tests_failed;
}