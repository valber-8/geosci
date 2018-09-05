#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include <sys/time.h>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;
std::vector<uint64_t> expand_whole_net(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec((layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
	uint64_t n;
	n=n_whole_net; 
	uint64_t agent;
	uint64_t h;
	h=(layer_whole_net-1)*neurons_per_layer*neurons_per_layer;
	for (uint64_t i=0;i<h;i++)
	{
		vec[i]=n%2;
		agent=n/2;
		n=agent;
	}
	return vec;
}
std::vector<uint64_t> expand_one_layer(uint64_t n_matrix, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec(neurons_per_layer*neurons_per_layer);
	uint64_t agent;
	uint64_t h;
	h=neurons_per_layer*neurons_per_layer;
	for (uint64_t i=0;i<h;i++)
	{
		vec[i]=n_matrix%2;
		agent=n_matrix/2;
		n_matrix=agent;
	}
	return vec;
}
uint64_t power_self(uint64_t mi){
	uint64_t aim;
	aim=1;
	for (uint64_t i=0;i<mi;i++)
	{
		aim=aim*2;
	}
	return aim;
}
uint64_t take_piece(uint64_t n_whole_net, uint64_t index_matrix, uint64_t layer_whole_net, uint64_t neurons_per_layer){
	uint64_t aim;
	uint64_t agent;
	aim=0;
	agent=n_whole_net;
{	
	
		if (0<index_matrix && index_matrix<layer_whole_net-2)
			{
			//cout<<"take in middle"<<endl;
			aim=agent%(power_self((index_matrix+1)*neurons_per_layer*neurons_per_layer));
			aim=aim/(power_self(index_matrix*neurons_per_layer*neurons_per_layer));			
			}
			
		if (index_matrix==0)
				{
				//cout<<"take first"<<endl;
				aim=agent%(power_self(((layer_whole_net-1)-(index_matrix+1))*neurons_per_layer*neurons_per_layer));
				//cout<<aim<<endl;	
				}
		if (index_matrix==layer_whole_net-2)
				{
				//cout<<"take last"<<endl;
				//cout<<index_matrix<<endl;
				aim=agent/(power_self(index_matrix*neurons_per_layer*neurons_per_layer));
				//cout<<aim<<endl;
				}
			}
		
		if (0>index_matrix || index_matrix>layer_whole_net-2)
		{	
			std::cout<<"no matrix"<<endl;
		}
	//cout<<"after this the n is "<<n_whole_net<<endl;	
	/*
	if (0<=index_matrix && index_matrix<=layer_whole_net-2)
	{
		if (0<index_matrix && index_matrix<layer_whole_net-2)
			{
			cout<<"take in middle"<<endl;
			aim=n_whole_net%(power_self((index_matrix+1)*neurons_per_layer*neurons_per_layer));
			aim=aim/(power_self(index_matrix*neurons_per_layer*neurons_per_layer));			
			}
		else 
			{	
			if (index_matrix==0)
				{
				cout<<"take first"<<endl;
				aim=n_whole_net%(power_self(((layer_whole_net-1)-(index_matrix+1))*neurons_per_layer*neurons_per_layer));
				cout<<aim<<endl;	
				}
			else // (index_matrix==layer_whole_net-2)
				{
				cout<<"take last"<<endl;
				aim=n_whole_net/(power_self(index_matrix*neurons_per_layer*neurons_per_layer));
				cout<<aim<<endl;
				}
			}
		
	}
	else
	{	
		std::cout<<"no matrix"<<endl;
	}
	*/
	
	return aim;
}
void show(const std::vector<uint64_t> &xs){
	
	for (const auto &x:xs)
	{
		std::cout <<x<<" ";
	}
	std::cout<<"\n";

}
void show_tensor(vector<uint64_t> &vect, uint64_t layer_whole_net, uint64_t neurons_per_layer){
	std::cout<<"this is tensor:"<<endl;
	for  (uint64_t i=0;i<(layer_whole_net-1)*neurons_per_layer*neurons_per_layer;i++)
		{
			std::cout<<vect[i]<<" ";
			if ((i+1)% neurons_per_layer==0)
				{
				if ((i+1)% (neurons_per_layer*neurons_per_layer)==0)
					{
						std::cout<<"**";
					}
				std::cout<<"\n";
				}
		}
		std::cout<<"\n";
}
void show_matrix(vector<uint64_t> &vect, uint64_t neurons_per_layer){	
	std::cout<<"this is metrix:"<<endl;
	for  (uint64_t i=0;i<neurons_per_layer*neurons_per_layer;i++)
		{
			std::cout<<vect[i]<<" ";
			if ((i+1)% neurons_per_layer==0)
				{
				std::cout<<"\n";
				}
		}
		std::cout<<"\n";
}
uint64_t count(vector<uint64_t> &xs,uint64_t vector_longth){
	uint64_t aim;
	aim=0;
	for (uint64_t i=0; i<vector_longth;i++)
	{
		aim=aim+xs[i]*power_self(i);
	}
	return aim;
}

std::vector<uint64_t> ex_rows_matrix(uint64_t n_matrix, uint64_t layer_whole_net, uint64_t neurons_per_layer, uint64_t index_row1,uint64_t index_row2 ) {
	std::vector<uint64_t> vec(neurons_per_layer*neurons_per_layer);
	vec=expand_one_layer(n_matrix, layer_whole_net, neurons_per_layer);
	uint64_t agent;
	for (uint64_t j=0;j<neurons_per_layer;j++)
		{		
			agent=vec[index_row1*neurons_per_layer+j];
			vec[index_row1*neurons_per_layer+j]=vec[index_row2*neurons_per_layer+j];
			vec[index_row2*neurons_per_layer+j]=agent;						
		}
	return vec;
}

std::vector<uint64_t> ex_columns_matrix(uint64_t n_matrix, uint64_t layer_whole_net, uint64_t neurons_per_layer, uint64_t index_column1,uint64_t index_column2 ) {
	std::vector<uint64_t> vec(neurons_per_layer*neurons_per_layer);
	vec=expand_one_layer(n_matrix, layer_whole_net, neurons_per_layer);
	uint64_t agent;
	for (uint64_t i=0;i<neurons_per_layer;i++)
		{		
			agent=vec[i*neurons_per_layer+index_column1];
			vec[i*neurons_per_layer+index_column1]=vec[i*neurons_per_layer+index_column2];
			vec[i*neurons_per_layer+index_column2]=agent;						
		}
	return vec;
}

std::vector<uint64_t> UD_turn_matrix(uint64_t n_matrix, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec(neurons_per_layer*neurons_per_layer);
	vec=expand_one_layer(n_matrix, layer_whole_net, neurons_per_layer);
	std::vector<uint64_t> agent(neurons_per_layer*neurons_per_layer);
	agent=expand_one_layer(n_matrix, layer_whole_net, neurons_per_layer);
	
	for (uint64_t k=0;k<neurons_per_layer;k++)
		{	
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{	
				agent[j*neurons_per_layer+k]=vec[(neurons_per_layer-1-j)*neurons_per_layer+k];
				}						
		}
	return agent;
}

std::vector<uint64_t> LR_turn_matrix(uint64_t n_matrix, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec(neurons_per_layer*neurons_per_layer);
	vec=expand_one_layer(n_matrix, layer_whole_net, neurons_per_layer);
	std::vector<uint64_t> agent(neurons_per_layer*neurons_per_layer);
	agent=expand_one_layer(n_matrix, layer_whole_net, neurons_per_layer);
	
	for (uint64_t j=0;j<neurons_per_layer;j++)
		{	
			for (uint64_t k=0;k<neurons_per_layer;k++)
				{	
				agent[j*neurons_per_layer+k]=vec[j*neurons_per_layer+neurons_per_layer-1-k];
				}						
		}
	return agent;
}

std::vector<uint64_t> UDLR_turn_matrix(uint64_t n_matrix, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec(neurons_per_layer*neurons_per_layer);
	vec=expand_one_layer(n_matrix, layer_whole_net, neurons_per_layer);
	std::vector<uint64_t> agent(neurons_per_layer*neurons_per_layer);
	agent=expand_one_layer(n_matrix, layer_whole_net, neurons_per_layer);
	
	for (uint64_t k=0;k<neurons_per_layer;k++)
		{	
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{	
				agent[j*neurons_per_layer+k]=vec[(neurons_per_layer-1-j)*neurons_per_layer+k];
				}						
		}
	for (uint64_t j=0;j<neurons_per_layer;j++)
		{	
			for (uint64_t k=0;k<neurons_per_layer;k++)
				{	
				vec[j*neurons_per_layer+k]=agent[j*neurons_per_layer+neurons_per_layer-1-k];
				}						
		}
	
	return vec;
}

std::vector<uint64_t> ex_lines_networks(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer, uint64_t index_line1,uint64_t index_line2) {
	
	std::vector<uint64_t> vec((layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
	vec=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer);
	uint64_t agent;
	
	for (uint64_t layer=1;layer<layer_whole_net;layer++)
		{
	
			//chagne rows
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{		
					agent=vec[(layer-1)*neurons_per_layer*neurons_per_layer+index_line1*neurons_per_layer+j];
					vec[(layer-1)*neurons_per_layer*neurons_per_layer+index_line1*neurons_per_layer+j]=vec[(layer-1)*neurons_per_layer*neurons_per_layer+index_line2*neurons_per_layer+j];
					vec[(layer-1)*neurons_per_layer*neurons_per_layer+index_line2*neurons_per_layer+j]=agent;						
				}
			//change columns 
			for (uint64_t i=0;i<neurons_per_layer;i++)
				{		
					agent=vec[(layer-1)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+index_line1];
					vec[(layer-1)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+index_line1]=vec[(layer-1)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+index_line2];
					vec[(layer-1)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+index_line2]=agent;						
				}
		}
	return vec;
}

std::vector<uint64_t> ex_points_networks(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer,uint64_t index_layer, uint64_t index_point1,uint64_t index_point2){
	
	std::vector<uint64_t> vec((layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
	vec=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer);
	
	uint64_t agent;
	
	if (0<index_layer && index_layer<layer_whole_net-1)
		{
		//chagne rows
		//cout<<"hello"<<endl;	
		for (uint64_t j=0;j<neurons_per_layer;j++)
			{		
				agent=vec[(index_layer-1)*neurons_per_layer*neurons_per_layer+index_point1*neurons_per_layer+j];
				vec[(index_layer-1)*neurons_per_layer*neurons_per_layer+index_point1*neurons_per_layer+j]=vec[(index_layer-1)*neurons_per_layer*neurons_per_layer+index_point2*neurons_per_layer+j];
				vec[(index_layer-1)*neurons_per_layer*neurons_per_layer+index_point2*neurons_per_layer+j]=agent;					
			}
		//change columns 
		for (uint64_t i=0;i<neurons_per_layer;i++)
			{		
				agent=vec[(index_layer)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+index_point1];
				vec[(index_layer)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+index_point1]=vec[(index_layer)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+index_point2];
				vec[(index_layer)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+index_point2]=agent;						
			}	
		}
	else
		{	
		if (index_layer==0)
			{
			//change columns 
			for (uint64_t i=0;i<neurons_per_layer;i++)
				{		
					agent=vec[i*neurons_per_layer+index_point1];
					
					/*
					vec[i*neurons_per_layer+index_point1]=vec_agent[i*neurons_per_layer+index_point2];
					vec[i*neurons_per_layer+index_point2]=vec_agent[i*neurons_per_layer+index_point1];
					show_matrix(vec_agent, neurons_per_layer);
					*/			
					vec[i*neurons_per_layer+index_point1]=vec[i*neurons_per_layer+index_point2];
					vec[i*neurons_per_layer+index_point2]=agent;
					//cout<<"rows"<<endl;						
				}
			}
		else
		//chagne rows
			{		
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{	
					//cout<<"exchange rows in last layer"<<endl;	
					agent=vec[(index_layer-1)*neurons_per_layer*neurons_per_layer+index_point1*neurons_per_layer+j];
					vec[(index_layer-1)*neurons_per_layer*neurons_per_layer+index_point1*neurons_per_layer+j]=vec[(index_layer-1)*neurons_per_layer*neurons_per_layer+index_point2*neurons_per_layer+j];
					vec[(index_layer-1)*neurons_per_layer*neurons_per_layer+index_point2*neurons_per_layer+j]=agent;						
				}
			}
		}
	
	//cout<<"the end"<<endl;
	return vec;	
}

std::vector<uint64_t> turn_whole_net(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec((layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
	vec=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer); 
	std::vector<uint64_t> vec_agent(neurons_per_layer*neurons_per_layer);
	uint64_t n_matrix;	
	for (uint64_t layer=1;layer<layer_whole_net;layer++)
		{					
		n_matrix=take_piece(n_whole_net, layer-1, layer_whole_net, neurons_per_layer);
		vec_agent=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
		show_matrix(vec_agent, neurons_per_layer);	
		vec_agent=UDLR_turn_matrix(n_matrix, layer_whole_net, neurons_per_layer);
		//show_matrix(vec_agent, neurons_per_layer);
		for (uint64_t j=0;j<neurons_per_layer;j++)
			{
			for (uint64_t k=0;k<neurons_per_layer;k++)
				{
				vec[(layer-1)*neurons_per_layer*neurons_per_layer+j*neurons_per_layer+k]=vec_agent[j*neurons_per_layer+k];	
				}	
			}	
		}
	return vec;
}

std::vector<uint64_t> sum_rows_tessor(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec((layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
	vec=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer); 
	std::vector<uint64_t> vec_agent((layer_whole_net-1)*neurons_per_layer);
	for (uint64_t layer=1;layer<layer_whole_net;layer++)
		{					
		for (uint64_t j=0;j<neurons_per_layer;j++)
			{
			vec_agent[(layer-1)*neurons_per_layer+j]=0;
			for (uint64_t k=0;k<neurons_per_layer;k++)
				{
				vec_agent[(layer-1)*neurons_per_layer+j]=vec[(layer-1)*neurons_per_layer*neurons_per_layer+j*neurons_per_layer+k]+vec_agent[(layer-1)*neurons_per_layer+j];	
				}	
			}	
		}
	return vec_agent;
}

std::vector<uint64_t> sum_columns_tessor(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec((layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
	vec=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer); 
	std::vector<uint64_t> vec_agent((layer_whole_net-1)*neurons_per_layer);
	for (uint64_t layer=1;layer<layer_whole_net;layer++)
		{					
		for (uint64_t k=0;k<neurons_per_layer;k++)
			{
			vec_agent[(layer-1)*neurons_per_layer+k]=0;
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{
				vec_agent[(layer-1)*neurons_per_layer+k]=vec[(layer-1)*neurons_per_layer*neurons_per_layer+j*neurons_per_layer+k]+vec_agent[(layer-1)*neurons_per_layer+k];	
				}	
			}	
		}
	return vec_agent;
}

uint64_t check_sick(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> sum_rows((layer_whole_net-1)*neurons_per_layer);
	sum_rows=sum_rows_tessor(n_whole_net, layer_whole_net, neurons_per_layer);
	std::vector<uint64_t> sum_columns((layer_whole_net-1)*neurons_per_layer);
	sum_columns=sum_columns_tessor(n_whole_net, layer_whole_net, neurons_per_layer);
	uint64_t agent_columns;
	
	for (uint64_t layer=1;layer<layer_whole_net;layer++)
		{	
		agent_columns=0;				
		for (uint64_t k=0;k<neurons_per_layer;k++)
			{
			agent_columns=agent_columns+sum_columns[(layer-1)*neurons_per_layer+k];
			}
		if (agent_columns==0)
			{
			//cout<<n_whole_net<<"has layer which only not has 0"<<endl;
			return 0;
			}				
		}
		
	for (uint64_t layer=1;layer<layer_whole_net-1;layer++)
		{					
		for (uint64_t j=0;j<neurons_per_layer;j++)
			{
			if ((sum_rows[(layer-1)*neurons_per_layer+j]+sum_columns[layer*neurons_per_layer+j]>0) && (sum_rows[(layer-1)*neurons_per_layer+j]*sum_columns[layer*neurons_per_layer+j]==0))
				{	
				//cout<<n_whole_net<<" has bad n"<<endl;			
				return 0;
				}
			}				
		}
	return 1;
}

uint64_t standard_struc(vector<uint64_t> &vect,  uint64_t neurons_per_layer) {

	uint64_t struc;	
	struc=0;			
	for (uint64_t jk=0;jk<neurons_per_layer;jk++)
		{
		if (vect[jk]>0)
			{
			struc=struc+1;
			}
		}		
	for (uint64_t jk=0;jk<struc;jk++)
		{
		if (vect[jk]==0)
			{
			return 0;
			}
		//cout<<"what"<<endl;	
		}
	//cout<<struc<<"struc"<<endl;											
	return struc;
}

std::vector<uint64_t> sum_rows_matrix(uint64_t n_whole_net,uint64_t layer_whole_net, uint64_t neurons_per_layer,uint64_t index_layer) {
	
	std::vector<uint64_t> vec_agent(neurons_per_layer);	
	uint64_t n_matrix;	
	//cout<<n_matrix3<<" "<<n_whole_net<<" "<<layer_whole_net<<" "<<neurons_per_layer<<endl;
	n_matrix=take_piece(n_whole_net,index_layer-1, layer_whole_net, neurons_per_layer);
	//cout<< "wuyunle"<<endl;
	//cout<<n_matrix3<<" "<<n_whole_net<<" "<<layer_whole_net<<" "<<neurons_per_layer<<endl;
	//cout<<n_matrix3<<" is right or not in sum_rows_m "<<endl;
	
	std::vector<uint64_t> vec_matrix(neurons_per_layer*neurons_per_layer);	
	vec_matrix=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	//show_matrix(vec_matrix, neurons_per_layer);
	//show_matrix(vec_matrix3, neurons_per_layer);
	for (uint64_t j=0;j<neurons_per_layer;j++)
			{
			vec_agent[j]=0;
			for (uint64_t k=0;k<neurons_per_layer;k++)
				{
				//cout<<"k"<<k<<" is "<<vec_matrix[j*neurons_per_layer+k]<<endl;
				vec_agent[j]=vec_matrix[j*neurons_per_layer+k]+vec_agent[j];	
				}
			//cout<<"sum_row"<<j<<" is "<<vec_agent[j]<<endl;	
			}
	return vec_agent;
}

std::vector<uint64_t> sum_columns_matrix(uint64_t n_whole_net,uint64_t layer_whole_net, uint64_t neurons_per_layer,uint64_t index_layer) {
	
	std::vector<uint64_t> vec_agent(neurons_per_layer);	
	uint64_t n_matrix;	
	n_matrix=take_piece(n_whole_net,index_layer-1, layer_whole_net, neurons_per_layer);
	std::vector<uint64_t> vec_matrix(neurons_per_layer*neurons_per_layer);	
	vec_matrix=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	
	for (uint64_t k=0;k<neurons_per_layer;k++)
			{
			vec_agent[k]=0;
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{
				//cout<<"k"<<k<<" is "<<vec_matrix[j*neurons_per_layer+k]<<endl;
				vec_agent[k]=vec_matrix[j*neurons_per_layer+k]+vec_agent[k];	
				}
			//cout<<"sum_row"<<j<<" is "<<vec_agent[j]<<endl;	
			}
	return vec_agent;
}

std::vector<uint64_t> check_struc(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> struc_agent(layer_whole_net);
	
	std::vector<uint64_t> columns_matrix(neurons_per_layer);
	std::vector<uint64_t> rows_matrix(neurons_per_layer);
	std::vector<uint64_t> vec(neurons_per_layer*neurons_per_layer);
	uint64_t n_matrix;
	n_matrix=take_piece(n_whole_net,0, layer_whole_net, neurons_per_layer);		
	vec=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	columns_matrix=sum_columns_matrix(n_whole_net, layer_whole_net,  neurons_per_layer,1);
	struc_agent[0]=standard_struc(columns_matrix,neurons_per_layer);	
	//cout<<"struc_agent[0] is "<<struc_agent[0]<<endl;
	for (uint64_t layer=1;layer<layer_whole_net;layer++)
		{
		rows_matrix=sum_rows_matrix(n_whole_net,layer_whole_net,neurons_per_layer,layer);				
		struc_agent[layer]=standard_struc(rows_matrix,neurons_per_layer);	
		//cout<<"struc_agent ["<<layer<<"] is "<<struc_agent[layer]<<endl;			
		}
	
	return struc_agent;	
}

uint64_t fit_check(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	
	std::vector<uint64_t> struc_agent(layer_whole_net);
	struc_agent=check_struc(n_whole_net, layer_whole_net, neurons_per_layer);	
	
	uint64_t health;
	health=check_sick(n_whole_net, layer_whole_net, neurons_per_layer);
	if (health==0)
			{
			//cout<<n_whole_net<<" is not health!"<<endl;
			return 0;
			}
	else
	{
	for (uint64_t layer=0;layer<layer_whole_net;layer++)
		{
			//cout<<struc_agent[layer]<<"###"<<endl;
		if (struc_agent[layer]==0)
			{
			//cout<<n_whole_net<<" has bad structure!"<<endl;
			return 0;
			}		
		}	
	}											
	return 1;
}

std::vector<uint64_t> sque_vector(vector<uint64_t> &vect, uint64_t neurons_per_layer) {
	
	std::vector<uint64_t> vec_agent(neurons_per_layer);	
	std::vector<uint64_t> indicator_if_used(neurons_per_layer);
	uint64_t agent_address;	
	uint64_t indicator_bigger_ornot;		
	uint64_t agent;
	for (uint64_t i=0;i<neurons_per_layer;i++)
			{
			 indicator_if_used[i]=0;			
			}	
	for (uint64_t i=0;i<neurons_per_layer;i++)
			{							
				if (i==0)
				{
					agent_address=0;
					for (uint64_t k=1;k<neurons_per_layer;k++)
					{				
						if(vect[k]>vect[agent_address])
						{
							agent_address=k;
						}
					
					}
				
				vec_agent[i]=agent_address;
				indicator_if_used[agent_address]=1;
				}
				
				else
				{								
					for (uint64_t k=0;k<neurons_per_layer;k++)
					{
						indicator_bigger_ornot=1;
						agent_address=k;
											
						if (indicator_if_used[k]==0 && vect[k]<=vect[vec_agent[i-1]])
							{
								for (uint64_t s=0;s<neurons_per_layer;s++)
								{
									
									if(indicator_if_used[s]==0)
									{	
										agent=0;
										if(vect[k]>=vect[s])
										{
											agent=1;
										}
									
									indicator_bigger_ornot=indicator_bigger_ornot*agent;	
									
									}
									
								}
							}						
								
					if(indicator_bigger_ornot==1 && indicator_if_used[k]==0)
						{
							vec_agent[i]=agent_address;
							indicator_if_used[agent_address]=1;
							break;
						}
					}																	
				}	
			}
							
			
	return vec_agent;
}

std::vector<uint64_t> muilt_rows_last_matrix(uint64_t n_whole_net,uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	
	std::vector<uint64_t> vec_agent(neurons_per_layer);	
	uint64_t n_matrix;	
	n_matrix=take_piece(n_whole_net,layer_whole_net-2, layer_whole_net, neurons_per_layer);
	std::vector<uint64_t> vec_matrix(neurons_per_layer*neurons_per_layer);	
	vec_matrix=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	
	for (uint64_t j=0;j<neurons_per_layer;j++)
			{
			vec_agent[j]=1;
			for (uint64_t k=0;k<neurons_per_layer;k++)
				{				
				vec_agent[j]=vec_matrix[j*neurons_per_layer+k]*vec_agent[j];	
				}			
			}
	return vec_agent;
}

std::vector<uint64_t> muilt_columns_matrix(uint64_t n_whole_net,uint64_t layer_whole_net, uint64_t neurons_per_layer,uint64_t index_layer) {
	
	std::vector<uint64_t> vec_agent(neurons_per_layer);	
	uint64_t n_matrix;	
	n_matrix=take_piece(n_whole_net,index_layer-1, layer_whole_net, neurons_per_layer);
	std::vector<uint64_t> vec_matrix(neurons_per_layer*neurons_per_layer);	
	vec_matrix=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	
	for (uint64_t k=0;k<neurons_per_layer;k++)
			{
			vec_agent[k]=1;
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{				
				vec_agent[k]=vec_matrix[j*neurons_per_layer+k]*vec_agent[k];	
				}			
			}
	return vec_agent;
}

std::vector<uint64_t> muilt_columns_rows(uint64_t n_whole_net,uint64_t layer_whole_net, uint64_t neurons_per_layer,uint64_t index_layer) {
	
	std::vector<uint64_t> vec_agent(neurons_per_layer);	
	uint64_t n_matrix;
	std::vector<uint64_t> vec_matrix(neurons_per_layer*neurons_per_layer);
		
	n_matrix=take_piece(n_whole_net,index_layer-1, layer_whole_net, neurons_per_layer);	
	vec_matrix=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	
	for (uint64_t k=0;k<neurons_per_layer;k++)
			{
			vec_agent[k]=1;
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{				
				vec_agent[k]=vec_matrix[j*neurons_per_layer+k]*vec_agent[k];	
				}			
			}
			
	n_matrix=take_piece(n_whole_net,index_layer-2, layer_whole_net, neurons_per_layer);	
	vec_matrix=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
		
	for (uint64_t k=0;k<neurons_per_layer;k++)
			{
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{				
				vec_agent[k]=vec_matrix[j*neurons_per_layer+k]*vec_agent[k];	
				}			
			}	
	return vec_agent;
}

std::vector<uint64_t> Full_arrangement(uint64_t neurons_per_layer) { //将全排列组成一个向量
	uint64_t situation=1;
	uint64_t arr[neurons_per_layer];
	for (uint64_t j=neurons_per_layer;j>0;j--)
			{
			situation=situation*j;
			arr[j-1]=j-1;
			}          
	std::vector<uint64_t> vec(situation*neurons_per_layer);	
	uint64_t i=0;
    do
    {
        for (uint64_t j=0;j<neurons_per_layer;j++)
			{			
			vec[i*neurons_per_layer+j]=arr[j];
			//cout << vec[i*neurons_per_layer+j]<<' ';
			}      
       // cout<<'\n';
        i++;
    }
    while ( next_permutation(arr,arr+neurons_per_layer) ); 
	return vec;
}

std::vector<uint64_t> sort_rows_by_order(vector<uint64_t> &vect, vector<uint64_t> &order, uint64_t neurons_per_layer){
				
	vector<uint64_t> vect_agent(neurons_per_layer*neurons_per_layer);
		
	for (uint64_t i=0;i<neurons_per_layer;i++)
			{
				for (uint64_t j=0;j<neurons_per_layer;j++)
				{				
				vect_agent[i*neurons_per_layer+j]=vect[order[i]*neurons_per_layer+j];				
				} 
			} 
	//cout<<"row sorted"<<endl;         
	return vect_agent;
}

std::vector<uint64_t> sort_columns_by_order(vector<uint64_t> &vect, vector<uint64_t> &order, uint64_t neurons_per_layer){
				
	vector<uint64_t> vect_agent(neurons_per_layer*neurons_per_layer);
			
	for (uint64_t j=0;j<neurons_per_layer;j++)
			{
				for (uint64_t i=0;i<neurons_per_layer;i++)
				{				
				vect_agent[i*neurons_per_layer+j]=vect[i*neurons_per_layer+order[j]];				
				} 
			} 
	//cout<<"columns sorted"<<endl;         
	return vect_agent;
}

std::vector<uint64_t> min_last_matrix(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer){
	
	uint64_t n_matrix;
	n_matrix=take_piece(n_whole_net, layer_whole_net-2, layer_whole_net, neurons_per_layer);
	vector<uint64_t> vect(neurons_per_layer*neurons_per_layer);
	vect=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	//show_matrix(vect, neurons_per_layer);
	vector<uint64_t> vect_agent1(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent2(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent_min(neurons_per_layer*neurons_per_layer);
	vect_agent_min=vect;	
	std::vector<uint64_t> order1(neurons_per_layer);//用来描述变换方式
	std::vector<uint64_t> order2(neurons_per_layer);
	std::vector<uint64_t> change(2); //用来描述变换方式对应的索引
	uint64_t agent_min;
	agent_min=n_matrix;
	uint64_t agent;	 
	uint64_t situation=1;
	for (uint64_t j=neurons_per_layer;j>0;j--)
		{
			situation=situation*j;
		} 
			
	std::vector<uint64_t> order_all(situation*neurons_per_layer);
	order_all=Full_arrangement(neurons_per_layer);
							
	for (uint64_t i=0;i<situation;i++)
		{
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{							
				order1[j]=order_all[i*neurons_per_layer+j];								
				}
				
			vect_agent1=sort_rows_by_order(vect, order1, neurons_per_layer);
			//cout<<"change columns***************"<<endl;
			//show_matrix(vect_agent1, neurons_per_layer);	
			for (uint64_t m=0;m<situation;m++)
				{
				
				for (uint64_t n=0;n<neurons_per_layer;n++)
					{												
					order2[n]=order_all[m*neurons_per_layer+n];										
					}
				
				vect_agent2=sort_columns_by_order(vect_agent1, order2, neurons_per_layer);					
				agent=count(vect_agent2,neurons_per_layer*neurons_per_layer);
				//show_matrix(vect_agent2, neurons_per_layer);
				if (agent<agent_min){
					vect_agent_min=vect_agent2;
					//cout<<"this is min"<<endl;
					//show_matrix(vect_agent_min, neurons_per_layer);
					agent_min=agent;
					change[0]=i;
					change[1]=m;
					}						
				}						
		}
	//cout<<"last matrix after sort"<<endl;
	//show_matrix(vect_agent_min, neurons_per_layer); 	
	return 	change;	
}

std::vector<uint64_t> global_min_tensor(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer){
	
	uint64_t h;
	h=(layer_whole_net-1)*neurons_per_layer*neurons_per_layer;
	vector<uint64_t> vect_agent(h); 
		
	uint64_t n_matrix_index1;
	n_matrix_index1=take_piece(n_whole_net, layer_whole_net-2, layer_whole_net, neurons_per_layer);
	vector<uint64_t> vect1(neurons_per_layer*neurons_per_layer);
	vect1=expand_one_layer(n_matrix_index1, layer_whole_net,neurons_per_layer);
	//cout<<"o m1***************"<<endl;
	//show_matrix(vect1, neurons_per_layer);
	
	uint64_t n_matrix_index0;
	n_matrix_index0=take_piece(n_whole_net, 0, layer_whole_net, neurons_per_layer);
	vector<uint64_t> vect0(neurons_per_layer*neurons_per_layer);
	vect0=expand_one_layer(n_matrix_index0, layer_whole_net,neurons_per_layer);
	//cout<<"o m0***************"<<endl;
	//show_matrix(vect0, neurons_per_layer);
	
	vector<uint64_t> vect_agent1(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent2(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent3(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent4(neurons_per_layer*neurons_per_layer);
			
	std::vector<uint64_t> order1(neurons_per_layer);//用来描述变换方式
	std::vector<uint64_t> order2(neurons_per_layer);
	std::vector<uint64_t> order3(neurons_per_layer);
	std::vector<uint64_t> change(3); //用来描述变换方式对应的索引
	
	uint64_t agent_min;
	agent_min=n_whole_net;
	uint64_t agent;
		 
	uint64_t situation=1;
	for (uint64_t j=neurons_per_layer;j>0;j--)
		{
			situation=situation*j;
		} 
			
	std::vector<uint64_t> order_all(situation*neurons_per_layer);
	order_all=Full_arrangement(neurons_per_layer);
							
	for (uint64_t i=0;i<situation;i++)
		{
			for (uint64_t j=0;j<neurons_per_layer;j++)
				{							
				order1[j]=order_all[i*neurons_per_layer+j];								
				}
				
			vect_agent1=sort_rows_by_order(vect1, order1, neurons_per_layer);//最后一层的行变换
			//cout<<"change rows of m1***************"<<endl;
			//show_matrix(vect_agent1, neurons_per_layer);	
			for (uint64_t m=0;m<situation;m++)
				{
				
				for (uint64_t n=0;n<neurons_per_layer;n++)
					{												
					order2[n]=order_all[m*neurons_per_layer+n];										
					}
				
				vect_agent2=sort_columns_by_order(vect_agent1, order2, neurons_per_layer);
				//cout<<"change columns of m1***************"<<endl;
				//show_matrix(vect_agent2, neurons_per_layer);	
				
				vect_agent3=sort_rows_by_order(vect0, order2, neurons_per_layer);//变换后的最后一层的列和前一层的行按order2变换
				//cout<<"change rows of m0***************"<<endl;
				//show_matrix(vect_agent3, neurons_per_layer);	
					
					for (uint64_t e=0;e<situation;e++)
						{
						
						for (uint64_t f=0;f<neurons_per_layer;f++)
							{												
							order3[f]=order_all[e*neurons_per_layer+f];										
							}
						
							vect_agent4=sort_columns_by_order(vect_agent3, order3, neurons_per_layer);
							//cout<<"change columns of m0***************"<<endl;
							//show_matrix(vect_agent4, neurons_per_layer);
							
							//show_matrix(vect_agent2, neurons_per_layer);
							//将a中元素全部拷贝到b开始的位置中,注意拷贝的区间为a.begin() ~ a.end()的左闭右开的区间*/
							//copy(a.begin(), a.end(), b.begin());
							//拷贝区间也可以是数组地址构成的区间
							
							copy(vect_agent4.begin(), vect_agent4.end(), vect_agent.begin());
							copy(vect_agent2.begin(), vect_agent2.end(), vect_agent.begin() + neurons_per_layer*neurons_per_layer);
							
							agent=count(vect_agent,h);
							//cout<<agent<<endl;			
							
							if (agent<agent_min){
								
								//cout<<"this is min"<<endl;
								//show_matrix(vect_agent_min, neurons_per_layer);
								agent_min=agent;
								
								change[0]=i;
								change[1]=m;
								change[2]=e;
								}						
						}
				}					
		}
	//cout<<"last matrix after sort"<<endl;
	//show_matrix(vect_agent_min, neurons_per_layer); 	
	return 	change;	
}


uint64_t min_normal_matrix(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer,uint64_t index_layer){
	
	uint64_t n_matrix;
	n_matrix=take_piece(n_whole_net, index_layer-1, layer_whole_net, neurons_per_layer);
	vector<uint64_t> vect(neurons_per_layer*neurons_per_layer);
	vect=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	//show_matrix(vect, neurons_per_layer);
	vector<uint64_t> vect_agent1(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent2(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent_min(neurons_per_layer*neurons_per_layer);
	vect_agent_min=vect;	
	std::vector<uint64_t> order2(neurons_per_layer);
	uint64_t change;
	uint64_t agent_min;
	agent_min=n_matrix;
	uint64_t agent;	 
	uint64_t situation=1;
	for (uint64_t j=neurons_per_layer;j>0;j--)
		{
			situation=situation*j;
		} 
			
	std::vector<uint64_t> order_all(situation*neurons_per_layer);
	order_all=Full_arrangement(neurons_per_layer);				
	vect_agent1=vect;
	//cout<<"change columns***************"<<endl;
	//show_matrix(vect_agent1, neurons_per_layer);	
	for (uint64_t m=0;m<situation;m++)
		{
				
		for (uint64_t n=0;n<neurons_per_layer;n++)
			{												
				order2[n]=order_all[m*neurons_per_layer+n];										
			}
				
			vect_agent2=sort_columns_by_order(vect_agent1, order2, neurons_per_layer);					
			agent=count(vect_agent2,neurons_per_layer*neurons_per_layer);
			//show_matrix(vect_agent2, neurons_per_layer);
			if (agent<agent_min){
				vect_agent_min=vect_agent2;
				//cout<<"this is min"<<endl;
				//show_matrix(vect_agent_min, neurons_per_layer);
				agent_min=agent;
				//change[0]=i;
				change=m;
				}						
		}						
		
	//cout<<"end"<<endl;
	//show_matrix(vect_agent_min, neurons_per_layer); 	
	return 	change;	
}



uint64_t global_min_reformation(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer){
	
	uint64_t h;
	h=(layer_whole_net-1)*neurons_per_layer*neurons_per_layer;
	vector<uint64_t> vect_agent(h); 
		
	uint64_t n_matrix_index1;
	n_matrix_index1=take_piece(n_whole_net, layer_whole_net-2, layer_whole_net, neurons_per_layer);
	vector<uint64_t> vect1(neurons_per_layer*neurons_per_layer);
	vect1=expand_one_layer(n_matrix_index1, layer_whole_net,neurons_per_layer);
	
	uint64_t n_matrix_index0;
	n_matrix_index0=take_piece(n_whole_net, 0, layer_whole_net, neurons_per_layer);
	vector<uint64_t> vect0(neurons_per_layer*neurons_per_layer);
	vect0=expand_one_layer(n_matrix_index0, layer_whole_net,neurons_per_layer);
	
	vector<uint64_t> vect_agent1(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent2(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent3(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_agent4(neurons_per_layer*neurons_per_layer);
	
	
		
	std::vector<uint64_t> order1(neurons_per_layer);//用来描述变换方式
	std::vector<uint64_t> order2(neurons_per_layer);
	std::vector<uint64_t> order3(neurons_per_layer);
	
	std::vector<uint64_t> change(3); //用来描述变换方式对应的索引
	
	change=global_min_tensor(n_whole_net, layer_whole_net,neurons_per_layer);
	
	
	
		 
	uint64_t situation=1;
	for (uint64_t j=neurons_per_layer;j>0;j--)
		{
			situation=situation*j;
		} 
			
	std::vector<uint64_t> order_all(situation*neurons_per_layer);
	order_all=Full_arrangement(neurons_per_layer);
	
	for (uint64_t n=0;n<neurons_per_layer;n++)
		{												
		order1[n]=order_all[change[0]*neurons_per_layer+n];										
		}
	for (uint64_t n=0;n<neurons_per_layer;n++)
		{												
		order2[n]=order_all[change[1]*neurons_per_layer+n];										
		}
	for (uint64_t n=0;n<neurons_per_layer;n++)
		{												
		order3[n]=order_all[change[2]*neurons_per_layer+n];										
		}						
	
				
	vect_agent1=sort_rows_by_order(vect1, order1, neurons_per_layer);//最后一层的行变换				
	vect_agent2=sort_columns_by_order(vect_agent1, order2, neurons_per_layer);
	vect_agent3=sort_rows_by_order(vect0, order2, neurons_per_layer);//变换后的最后一层的列和前一层的行按order2变换						
	vect_agent4=sort_columns_by_order(vect_agent3, order3, neurons_per_layer);
					
							
	//show_matrix(vect_agent2, neurons_per_layer);
	//将a中元素全部拷贝到b开始的位置中,注意拷贝的区间为a.begin() ~ a.end()的左闭右开的区间*/
	//copy(a.begin(), a.end(), b.begin());
	//拷贝区间也可以是数组地址构成的区间
							
	copy(vect_agent4.begin(), vect_agent4.end(), vect_agent.begin());
	copy(vect_agent2.begin(), vect_agent2.end(), vect_agent.begin() + neurons_per_layer*neurons_per_layer);	
	uint64_t agent;					
	agent=count(vect_agent,h);
			
	return 	agent;	
	
	
}









uint64_t min_reformation(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer){
	uint64_t h;
	h=(layer_whole_net-1)*neurons_per_layer*neurons_per_layer;
	vector<uint64_t> vect_agent(h); 
	vector<uint64_t> vect;
	vect=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer);
	vect_agent=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer);
	
	std::vector<uint64_t> change(2);
	uint64_t order_index;
	std::vector<uint64_t> order(neurons_per_layer);
	
	uint64_t new_n_whole_net;	
	uint64_t situation=1;
	
	for (uint64_t j=neurons_per_layer;j>0;j--)
		{
			situation=situation*j;
		} 
	std::vector<uint64_t> order_all(situation*neurons_per_layer);
	order_all=Full_arrangement(neurons_per_layer);			
		
	change= min_last_matrix(n_whole_net, layer_whole_net, neurons_per_layer);
	
	// sort rows of last matrix
	order_index=change[0];	
	for (uint64_t j=0;j<neurons_per_layer;j++)
		{							
			order[j]=order_all[order_index*neurons_per_layer+j];								
		}		
	for (uint64_t i=0;i<neurons_per_layer;i++)
			{
				for (uint64_t j=0;j<neurons_per_layer;j++)
				{				
				vect_agent[(layer_whole_net-2)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+j]=vect[(layer_whole_net-2)*neurons_per_layer*neurons_per_layer+order[i]*neurons_per_layer+j];				
				} 
			}
	vect=vect_agent;
	new_n_whole_net=count(vect,(layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
	/*
	uint64_t n_matrix;
	n_matrix=take_piece(new_n_whole_net, 1, layer_whole_net, neurons_per_layer);
	vector<uint64_t> vectxx(neurons_per_layer*neurons_per_layer);
	vectxx=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	cout<< "sort rows of last matrix"<<endl;
	show_matrix(vectxx, neurons_per_layer);
	*/
	for (uint64_t ly=layer_whole_net-1;ly>0;ly--) //ly is index of net layer, not index of matrix
			{
				if 	(ly==layer_whole_net-1) 
					{
						
						// sort columns of last matrix
						order_index=change[1];
						for (uint64_t j=0;j<neurons_per_layer;j++)
							{							
								order[j]=order_all[order_index*neurons_per_layer+j];								
							}
							
						for (uint64_t j=0;j<neurons_per_layer;j++)
							{
								for (uint64_t i=0;i<neurons_per_layer;i++)
								{				
									vect_agent[(layer_whole_net-2)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+j]=vect[(layer_whole_net-2)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+order[j]];				
								} 
							} 
						// sort rows of -1 matrix
						for (uint64_t i=0;i<neurons_per_layer;i++)
							{
								for (uint64_t j=0;j<neurons_per_layer;j++)
								{				
									vect_agent[(layer_whole_net-3)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+j]=vect[(layer_whole_net-3)*neurons_per_layer*neurons_per_layer+order[i]*neurons_per_layer+j];				
								} 
							}
						vect=vect_agent;
						new_n_whole_net=count(vect,(layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
						/*
						n_matrix=take_piece(new_n_whole_net, 1, layer_whole_net, neurons_per_layer);
						vector<uint64_t> vectxx(neurons_per_layer*neurons_per_layer);
						vectxx=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
						cout<< "sort colmns of last matrix"<<endl;
						show_matrix(vectxx, neurons_per_layer);	
						*/					
					}
					
				if 	((1<ly)&&(ly<layer_whole_net-1))
					{					
						// search the order index, the sort of rows have been done in last step
						order_index=min_normal_matrix(new_n_whole_net, layer_whole_net, neurons_per_layer, ly);
						// sort columns
						for (uint64_t j=0;j<neurons_per_layer;j++)
							{							
								order[j]=order_all[order_index*neurons_per_layer+j];								
							}
							
						for (uint64_t j=0;j<neurons_per_layer;j++)
							{
								for (uint64_t i=0;i<neurons_per_layer;i++)
								{				
									vect_agent[(ly-1)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+j]=vect[(ly-1)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+order[j]];				
								} 
							} 
						// sort rows of previous matrix
						for (uint64_t i=0;i<neurons_per_layer;i++)
							{
								for (uint64_t j=0;j<neurons_per_layer;j++)
								{				
									vect_agent[(ly-2)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+j]=vect[(ly-2)*neurons_per_layer*neurons_per_layer+order[i]*neurons_per_layer+j];				
								} 
							}
						vect=vect_agent;
						new_n_whole_net=count(vect,(layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
						cout<<new_n_whole_net<<endl;						
					}	
				if 	(1==ly)
					{	
										
						// search the order index, the sort of rows have been done in last step
						order_index=min_normal_matrix(new_n_whole_net, layer_whole_net, neurons_per_layer, ly);
						// sort columns
						for (uint64_t j=0;j<neurons_per_layer;j++)
							{							
								order[j]=order_all[order_index*neurons_per_layer+j];								
							}
							
						for (uint64_t j=0;j<neurons_per_layer;j++)
							{
								for (uint64_t i=0;i<neurons_per_layer;i++)
								{				
									vect_agent[(ly-1)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+j]=vect[(ly-1)*neurons_per_layer*neurons_per_layer+i*neurons_per_layer+order[j]];				
								} 
							} 
						// do not need to sort rows of previous matrix
						//
						vect=vect_agent;
						new_n_whole_net=count(vect,(layer_whole_net-1)*neurons_per_layer*neurons_per_layer);
						/*
						n_matrix=take_piece(new_n_whole_net, 0, layer_whole_net, neurons_per_layer);
						vectxx=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
						cout<< "sort rows of last matrix"<<endl;
						show_matrix(vectxx, neurons_per_layer);	
						*/						
					}	
			} 
	
	
	return 	new_n_whole_net;	
}

//将文本文件中得数据读入vector中，并返回一个vector。
std::vector<uint64_t> *InputData_To_Vector(string file_name){
    std::vector<uint64_t> *p = new vector<uint64_t>;
    ifstream infile(file_name);
    uint64_t number;
    while(! infile.eof())
    {
        infile >> number;
        p->push_back(number);
    }
    p->pop_back();  //此处要将最后一个数字弹出，是因为上述循环将最后一个数字读取了两次
    return p;
}


uint64_t put_together(uint64_t first_n_whole_net, uint64_t second_n_whole_net, uint64_t first_layer_whole_net, uint64_t second_layer_whole_net, uint64_t neurons_per_layer){
	
	
	uint64_t h;
	h=(first_layer_whole_net+second_layer_whole_net-3)*neurons_per_layer*neurons_per_layer;
	vector<uint64_t> vect_agent(h); 
	vector<uint64_t> first_vect;
	vector<uint64_t> second_vect;
	// first_vect=expand_whole_net(first_n_whole_net,first_layer_whole_net, neurons_per_layer);
	second_vect=expand_whole_net(second_n_whole_net,second_layer_whole_net, neurons_per_layer);
	
	vect_agent=expand_whole_net(first_n_whole_net,h, neurons_per_layer);
	
	//将a中元素全部拷贝到b开始的位置中,注意拷贝的区间为a.begin() ~ a.end()的左闭右开的区间*/
	//copy(a.begin(), a.end(), b.begin());
	//拷贝区间也可以是数组地址构成的区间
	/*
	copy(second_vect.begin(), second_vect.end(), vect_agent.begin() + neurons_per_layer*neurons_per_layer);
	*/
	//cout<<"copy start"<<endl;
	copy(second_vect.begin(), second_vect.end(), vect_agent.begin() +(h-2*neurons_per_layer*neurons_per_layer));
	//cout<<"copy end"<<endl;
	uint64_t new_n_whole_net;
	new_n_whole_net=count(vect_agent,h);
	return new_n_whole_net;
	
}

void combine(uint64_t first_layer_whole_net, uint64_t second_layer_whole_net, uint64_t neurons_per_layer){
	stringstream ss1;          //定义流ss
	stringstream ss2;          //定义流ss
	stringstream sst;          //定义流ss
   // ss << a;      将数字a转化成流ss
    //ss >> res;    将流ss转化成字符串
    
	string file_name1;
	ss1<<first_layer_whole_net<<".txt";
	ss1>>file_name1;
    cout<<file_name1<<endl;
    
    string file_name2;
    ss2<<second_layer_whole_net<<".txt";
	ss2>>file_name2;
    cout<<file_name2<<endl;
     
    string target_file_name;
    sst<<first_layer_whole_net+second_layer_whole_net-2<<".txt";
	sst>>target_file_name;
    cout<<target_file_name<<endl;
    
    
   // cout<<"load in"<<endl;
   
    vector<uint64_t> *s1= InputData_To_Vector(file_name1);
   // cout<<"load f1"<<endl;
    vector<uint64_t> *s2= InputData_To_Vector(file_name2);
   // cout<<"load f2"<<endl;
    
    vector<uint64_t>::iterator it1;
    vector<uint64_t>::iterator it2;
    
    
    uint64_t new_n_whole_net;
    
    ofstream outf;
    outf.open(target_file_name);
    
    for(it1=s1->begin(); it1!=s1->end(); it1++)
    {
        for(it2=s2->begin(); it2!=s2->end(); it2++)
		{
			uint64_t first_n_matrix;
			first_n_matrix=take_piece(*it1, first_layer_whole_net-2, first_layer_whole_net, neurons_per_layer);
			uint64_t second_n_matrix;
			second_n_matrix=take_piece(*it2, 0, second_layer_whole_net, neurons_per_layer);
			if (first_n_matrix==second_n_matrix)
				{
					new_n_whole_net=put_together(*it1, *it2, first_layer_whole_net, second_layer_whole_net,  neurons_per_layer);
					//outf<<*it1<<"*"<<*it2<<"*"<<new_n_whole_net<<endl;
					outf<<new_n_whole_net<<endl;
				}
			
			
		//	uint64_t first_n_matrix;
		//	first_n_matrix=take_piece(*it1, 1, first_layer_whole_net, neurons_per_layer);
		//	uint64_t second_n_matrix;
		//	second_n_matrix=take_piece(*it2, 0, second_layer_whole_net, neurons_per_layer);
		//	if (first_n_matrix==second_n_matrix)
		//		{
		//			new_n_whole_net=put_together(*it1, *it2, first_layer_whole_net, second_layer_whole_net,  neurons_per_layer);
		//			outf<<new_n_whole_net<<endl;
		//		}
			
				
		}
    }
    delete s1;
    delete s2;
	outf.close();
}


std::vector<uint64_t> expand_whole_net_to_two_nums(uint64_t n_whole_net, uint64_t layer_whole_net, uint64_t neurons_per_layer) {
	std::vector<uint64_t> vec(2);
	uint64_t n;
	n=n_whole_net; 
	uint64_t agent;
	agent=power_self(neurons_per_layer*neurons_per_layer); 	
	vec[0]=n%agent;
	//cout<<"1 is:"<<endl;
	//cout<<vec[0]<<endl;
	vec[1]=n/agent;
	//cout<<"2 is:"<<endl;
	//cout<<vec[1]<<endl;
	return vec;
}


int main(int argc, char* argv[]) {
	
	uint64_t n_whole_net;
	uint64_t layer_whole_net;
	uint64_t neurons_per_layer;
	uint64_t h;	
	//n_whole_net=511;
	layer_whole_net=3;
	neurons_per_layer=3;
	
	h=(layer_whole_net-1)*neurons_per_layer*neurons_per_layer;
	/*
	vector<uint64_t> vect(h);
	vect=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer); 
	show_tensor(vect, layer_whole_net, neurons_per_layer);
	cout<<"try"<<endl;
	
	uint64_t num;
	num=count(vect,h);
	cout<<num<<endl;
	
	uint64_t n_matrix;
	n_matrix=take_piece(n_whole_net, 0, layer_whole_net, neurons_per_layer);
	std::vector<uint64_t> vec(neurons_per_layer*neurons_per_layer);	
	vec=expand_one_layer(n_matrix, layer_whole_net,neurons_per_layer);
	show_matrix(vec, neurons_per_layer);
	
	std::vector<uint64_t> vec2(neurons_per_layer*neurons_per_layer);
	vec2=ex_columns_matrix(n_matrix, layer_whole_net, neurons_per_layer, 0,3 );
	show_matrix(vec2, neurons_per_layer);
	
	std::vector<uint64_t> vec3(neurons_per_layer*neurons_per_layer);
	vec3=ex_rows_matrix(n_matrix, layer_whole_net, neurons_per_layer, 0,3 );
	show_matrix(vec3, neurons_per_layer);
	
	std::vector<uint64_t> vec4(neurons_per_layer*neurons_per_layer);
	vec4=LR_turn_matrix(n_matrix, layer_whole_net, neurons_per_layer);
	show_matrix(vec4, neurons_per_layer);
	
	std::vector<uint64_t> vec5(neurons_per_layer*neurons_per_layer);
	vec5=UD_turn_matrix(n_matrix, layer_whole_net, neurons_per_layer);
	show_matrix(vec5, neurons_per_layer);
	
	std::vector<uint64_t> vec6(neurons_per_layer*neurons_per_layer);
	vec6=UDLR_turn_matrix(n_matrix, layer_whole_net, neurons_per_layer);
	show_matrix(vec6, neurons_per_layer);
	
	vector<uint64_t> vec7(h);
	vec7=ex_lines_networks(n_whole_net, layer_whole_net, neurons_per_layer, 3, 0);
	show_tensor(vec7, layer_whole_net, neurons_per_layer);
	
	
	vector<uint64_t> vec8(h);
	for (uint64_t k=0;k<4;k++){
	for (uint64_t i=0;i<4;i++){
		for (uint64_t j=0;j<4;j++){
		vec8=ex_points_networks(n_whole_net, layer_whole_net, neurons_per_layer,k, i, j);
		show_tensor(vec8, layer_whole_net, neurons_per_layer);
		}
		}
	}
	
	vector<uint64_t> vec9(h);
	vec9=turn_whole_net(n_whole_net, layer_whole_net, neurons_per_layer);
	show_tensor(vec9, layer_whole_net, neurons_per_layer);
	
	
	
	uint64_t health;
	health=check_sick(n_whole_net, layer_whole_net, neurons_per_layer);
	cout<<health<<endl;
	
	vector<uint64_t> vect(h);
	vect=expand_whole_net(n_whole_net,layer_whole_net, neurons_per_layer); 
	show_tensor(vect, layer_whole_net, neurons_per_layer);
	
	//uint64_t n_matrix1;
	//std::vector<uint64_t> vec1(neurons_per_layer*neurons_per_layer);		
	//n_matrix1=take_piece(n_whole_net,0, layer_whole_net, neurons_per_layer);		
	//vec1=expand_one_layer(n_matrix1, layer_whole_net,neurons_per_layer);
	//show_matrix(vec1, neurons_per_layer);
	//sum_rows_matrix(n_whole_net,layer_whole_net, neurons_per_layer,2);		
	//std::vector<uint64_t> struc_agent(layer_whole_net);
	//struc_agent=check_struc(n_whole_net, layer_whole_net, neurons_per_layer);
	fit_check(n_whole_net, layer_whole_net, neurons_per_layer);
	
	
	
	uint64_t count;
	count=0;
	ofstream outf; 
	outf.open("abc.txt");	
	for (uint64_t i=0;i<power_self(h);i++)
	
	//for (uint64_t i=1;i<2;i++)
		{
			uint64_t n_matrix;		
			if (fit_check(i, layer_whole_net, neurons_per_layer)>0)
			{			
			count=count+1;
			outf<<i<<endl;
			}		
		}
	outf.close();	
	cout<<count<<endl;
	
	
	
	uint64_t count;
	count=0;

	struct timeval t3, t4;
	gettimeofday(&t3, NULL);
	//for (uint64_t i=513;i<514;i++)
	for (uint64_t i=0;i<power_self(h);i++)
		{
			//vector<uint64_t> vect(h);
			//vect=expand_whole_net(i,layer_whole_net, neurons_per_layer); 
			//show_tensor(vect, layer_whole_net, neurons_per_layer);
			if (fit_check(i, layer_whole_net, neurons_per_layer)>0)
			{
			count=count+1;
			//outf<<i<<endl;
			}		
		}
	gettimeofday(&t4, NULL);  
	double deltaT2 = (t4.tv_sec-t3.tv_sec) * 1000000 + t4.tv_usec-t3.tv_usec;
	cout<<count<<endl;
	
	count=0;
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	#pragma omp parallel for reduction(+:count)
	for (uint64_t i=0;i<power_self(h);i++)
		{
			if (fit_check(i, layer_whole_net, neurons_per_layer)>0)
			{
			count=count+1;
			//outf<<i<<endl;
			}		
		}
	//#pragma omp barrier
	gettimeofday(&t2, NULL); 
	double deltaT1 = (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec;
	cout<<deltaT2<<endl;
	cout<<deltaT1<<endl;
	cout<<deltaT2/deltaT1<<endl;
	
	
	uint64_t a[5] = {1,2,3,4,5};

	std::vector<uint64_t> vect(a, a+5);
	
	sque_vector(vect, neurons_per_layer);
	
	
	
	
	
	//vect=expand_whole_net(new_n_whole_net,layer_whole_net, neurons_per_layer); 
	//show_tensor(vect, layer_whole_net, neurons_per_layer);
	return 0;
	
	
	
	uint64_t count;
	count=0;
	
	ofstream outf; 
	uint64_t new_n_whole_net;
	
	outf.open("abcd.txt");	
	for (uint64_t i=0;i<power_self(h);i++)
	
	//for (uint64_t i=1;i<2;i++)
		{
			uint64_t n_matrix;	
			cout<<i<<endl;	
			if (fit_check(i, layer_whole_net, neurons_per_layer)>0)
			{						
			new_n_whole_net=min_reformation(i,layer_whole_net, neurons_per_layer);
			count=count+1;
			outf<<new_n_whole_net<<"*"<<i<<endl;
			}		
		}
	outf.close();	
	cout<<count<<endl;
	
	
	
	uint64_t count;
	

	struct timeval t3, t4;
	gettimeofday(&t3, NULL);
	for (uint64_t i=0;i<24;i++)
		{
		count=0;
		for (uint64_t i=0;i<power_self(h);i++)
		{
			uint64_t n_matrix;		
			if (fit_check(i, layer_whole_net, neurons_per_layer)>0)
			{						
			new_n_whole_net=min_reformation(i,layer_whole_net, neurons_per_layer);
			count=count+1;
			}		
		}
		}
	gettimeofday(&t4, NULL);  
	double deltaT2 = (t4.tv_sec-t3.tv_sec) * 1000000 + t4.tv_usec-t3.tv_usec;
	
	
	
	struct timeval t1, t2;
	gettimeofday(&t1, NULL);
	
	#pragma omp parallel for reduction(+:count)
	for (uint64_t i=0;i<24;i++)
		{
		count=0;
		for (uint64_t i=0;i<power_self(h);i++)
		{
			uint64_t n_matrix;		
			if (fit_check(i, layer_whole_net, neurons_per_layer)>0)
			{						
			new_n_whole_net=min_reformation(i,layer_whole_net, neurons_per_layer);
			count=count+1;
			}		
		}
		}
	//#pragma omp barrier
	gettimeofday(&t2, NULL); 
	double deltaT1 = (t2.tv_sec-t1.tv_sec) * 1000000 + t2.tv_usec-t1.tv_usec;
	
	cout<<deltaT2<<endl;
	cout<<deltaT1<<endl;
	cout<<deltaT2/deltaT1<<endl;
		
	
        
        for(uint64_t i=3; i<7; i++)
		{
			combine(i, 3, neurons_per_layer);
		}
    
	
	expand_whole_net_to_two_nums(n_whole_net,layer_whole_net,neurons_per_layer);
    
    vector<uint64_t> *s1= InputData_To_Vector("abc.txt");
    vector<uint64_t>::iterator it1;
  
    uint64_t new_n_whole_net;
    
    ofstream outf1;
    outf1.open("global.txt");
    
    for(it1=s1->begin(); it1!=s1->end(); it1++)
    {        
		new_n_whole_net=global_min_reformation(*it1, layer_whole_net, neurons_per_layer);
		outf1<<*it1<<"*"<<new_n_whole_net<<endl;
    }
	outf1.close();
	
	
	
	
    vector<uint64_t> *s1= InputData_To_Vector("global_answer.txt");
    vector<uint64_t>::iterator it1;
  
    std::vector<uint64_t> vec(2);
    ofstream outf1;
    outf1.open("check.txt");
    
    for(it1=s1->begin(); it1!=s1->end(); it1++)
    {        
		vec=expand_whole_net_to_two_nums(*it1,layer_whole_net,neurons_per_layer);
		outf1<<vec[0]<<"*"<<vec[1]<<endl;
    }
	outf1.close();




	
	
	//按照分解后的第一个数字排序
    vector<uint64_t> *s1= InputData_To_Vector("global_answer.txt");
    vector<uint64_t>::iterator it1;
	std::vector<uint64_t> vec(2);
    std::vector<uint64_t> vec_first;
    std::vector<uint64_t> vec_second;
    //std::vector<uint64_t> vec_new_first;
    //std::vector<uint64_t> vec_new_second;
    uint64_t i=0;
    ofstream outf1;
    outf1.open("sort.txt");
    
    for(it1=s1->begin(); it1!=s1->end(); it1++)
    {        
		vec=expand_whole_net_to_two_nums(*it1,layer_whole_net,neurons_per_layer);
		vec_first.push_back(vec[0]);
		vec_second.push_back(vec[1]);
		i=i+1;
    }
    
    for (uint64_t j=0;j<power_self(neurons_per_layer*neurons_per_layer);j++)	
		{									
			for (uint64_t k=0;k<i;k++)	
			{			
				if 	(j==vec_first[k])
				{	
										
					//vec_new_first.push_back(j);
					//vec_new_second.push_back(vec_second[k]);
					outf1<<vec_first[k]<<"*"<<vec_second[k]<<endl;
				}
			}  
		}
		
    
	outf1.close();
	*/
	
	//生成第一种组合
	vector<uint64_t> *s1= InputData_To_Vector("global_answer.txt");
    vector<uint64_t>::iterator it1;
  
    std::vector<uint64_t> vec(2);
    std::vector<uint64_t> vec_first_num;
    std::vector<uint64_t> vec_second_num;
    //ofstream outf1;
   // outf1.open("address.txt");
    
    for(it1=s1->begin(); it1!=s1->end(); it1++)
    {        
		vec=expand_whole_net_to_two_nums(*it1,layer_whole_net,neurons_per_layer);
		vec_first_num.push_back(vec[0]);
		vec_second_num.push_back(vec[1]);
		
    }
    
	
	uint64_t longth;
    longth=vec_first_num.size();
    cout<<longth<<endl;
    
    
    std::vector<uint64_t> vec_address_start(longth);
    vec_address_start[0]=0;
    std::vector<uint64_t> vec_address_end(longth);
    uint64_t step=0;
    for (uint64_t i=0;i<longth-1;i++)	
		{								
		if 	(vec_second_num[i]==vec_second_num[i+1])
			{	
				vec_address_start[i+1]=vec_address_start[i];
				step=step+1;										
			}			
		else
			{
				vec_address_start[i+1]=i+1;
				vec_address_end[i]=i;
				 for (uint64_t k=0;k<step;k++)
				 {
					 vec_address_end[i-k-1]=i;
				 }
				 step=0;				
			}
		}
	 while (vec_second_num[longth-1-step]==vec_second_num[longth-2-step])
			{	
				step=step+1;										
			}			
		
	for (uint64_t k=0;k<step+1;k++)
			{
				vec_address_end[longth-k-1]=longth-1;
			}		
		
    //for (uint64_t i=0;i<longth;i++)	
		//{
		//outf1<<i<<" : "<<vec_first_num[i]<<"*"<<vec_second_num[i]<<"*"<<vec_address_start[i]<<"*"<<vec_address_end[i]<<endl;
		//}
	//outf1.close();
	
	
	
	//按照分解后的第一个数字排序

    std::vector<uint64_t> vec_new_first_num;
    std::vector<uint64_t> vec_new_second_num;
    //ofstream outf2;
   //outf2.open("sort.txt");
    
    for (uint64_t j=0;j<power_self(neurons_per_layer*neurons_per_layer);j++)	
		{									
			for (uint64_t k=0;k<longth;k++)	
			{			
				if 	(j==vec_first_num[k])
				{	
										
					vec_new_first_num.push_back(j);
					vec_new_second_num.push_back(vec_second_num[k]);
					//outf2<<vec_first_num[k]<<"*"<<vec_second_num[k]<<endl;
				}
			}  
		}	
    
	//outf2.close();
	
	//排序后计算地址
	//ofstream outf3;
    //outf3.open("address2.txt");
	std::vector<uint64_t> vec_new_address_start(longth);
    vec_new_address_start[0]=0;
    std::vector<uint64_t> vec_new_address_end(longth);
    step=0;
    for (uint64_t i=0;i<longth-1;i++)	
		{								
		if 	(vec_new_first_num[i]==vec_new_first_num[i+1])
			{	
				vec_new_address_start[i+1]=vec_new_address_start[i];
				step=step+1;										
			}			
		else
			{
				vec_new_address_start[i+1]=i+1;
				vec_new_address_end[i]=i;
				 for (uint64_t k=0;k<step;k++)
				 {
					 vec_new_address_end[i-k-1]=i;
				 }
				 step=0;				
			}
		}
	 while (vec_new_first_num[longth-1-step]==vec_new_first_num[longth-2-step])
			{	
				step=step+1;										
			}			
		
	for (uint64_t k=0;k<step+1;k++)
			{
				vec_new_address_end[longth-k-1]=longth-1;
			}		
		
    //for (uint64_t i=0;i<longth;i++)	
		//{
		//outf3<<i<<" : "<<vec_new_first_num[i]<<"*"<<vec_new_second_num[i]<<"*"<<vec_new_address_start[i]<<"*"<<vec_new_address_end[i]<<endl;
		//}
	//outf3.close();
	
	//ofstream outf4;
    //outf4.open("combine1.txt");
	std::vector<uint64_t> vec_agent(4);
	std::vector<uint64_t> vec_all_combine1;
	uint64_t address_for_com=0;
	uint64_t address_for_ca_start;
	uint64_t address_for_ca_end;
	uint64_t address_for_cb_start;
	uint64_t address_for_cb_end;
	while (address_for_com<longth)
		{	
			vec_agent[2]=vec_second_num[address_for_com]; //ec
			for (uint64_t i=vec_address_start[address_for_com];i<vec_address_end[address_for_com]+1;i++)
				{
				vec_agent[0]=vec_first_num[i];  //ca
				for (uint64_t j=vec_address_start[address_for_com];j<vec_address_end[address_for_com]+1;j++)
					{
						vec_agent[1]=vec_first_num[j];  //cb
						vec_agent[3]=0;  //cf
						
						vec_all_combine1.push_back(vec_agent[0]);
						vec_all_combine1.push_back(vec_agent[1]);
						vec_all_combine1.push_back(vec_agent[2]);
						
						//cout<<"ace is "<<vec_agent[0]<<"*"<<vec_agent[1]<<"*"<<vec_agent[2]<<endl;
						vec_all_combine1.push_back(vec_agent[3]);
						for (uint64_t k=0;k<longth;k++)	
							{
								if  (vec_new_first_num[k]==vec_agent[0])
								{
								address_for_ca_start=vec_new_address_start[k];
								address_for_ca_end=vec_new_address_end[k];
								break;
								}
							}	
						for (uint64_t k=0;k<longth;k++)	
							{
								if  (vec_new_first_num[k]==vec_agent[1])
								{
								address_for_cb_start=vec_new_address_start[k];
								address_for_cb_end=vec_new_address_end[k];
								break;
								}
							}
						for (uint64_t ca_i=address_for_ca_start;ca_i<address_for_ca_end+1;ca_i++)
							{				
							for (uint64_t cb_j=address_for_cb_start;cb_j<address_for_cb_end+1;cb_j++)
								{
									if  (vec_new_second_num[ca_i]==vec_new_second_num[cb_j])
										{								
											vec_all_combine1.push_back(vec_agent[0]);
											vec_all_combine1.push_back(vec_agent[1]);
											vec_all_combine1.push_back(vec_agent[2]);
											//outf4<<vec_agent[0]<<"*"<<vec_agent[1]<<"*"<<vec_agent[2]<<"*"<<vec_new_second_num[ca_i]<<endl;
											
											//cout<<"fc can be :"<<vec_new_second_num[ca_i]<<endl;
											vec_all_combine1.push_back(vec_new_second_num[ca_i]);
										}
								}
							}	
					}
				}				
			address_for_com=vec_address_end[address_for_com]+1;
		}
	
	//outf4.close();
	
	
	uint64_t longth_combine;
    longth_combine=vec_all_combine1.size();
	//std::vector<uint64_t> vec_new_agent(8);
		
	
	vector<uint64_t> vect_ca(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_cb(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_da(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_db(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_ec(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_ed(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_fc(neurons_per_layer*neurons_per_layer);
	vector<uint64_t> vect_fd(neurons_per_layer*neurons_per_layer);
	
	ofstream outf5;
    outf5.open("combine_f.txt");
    //cout<<"all is :"<<endl;
    //cout<<vec_all_combine1.size()/4<<endl;
    for (uint64_t i=0;i<vec_all_combine1.size()/4+1;i++)
	//for (uint64_t i=0;i<3;i++)
		{
		//for (uint64_t j=0;j<13;j++)				
		for (uint64_t j=0;j<vec_all_combine1.size()/4+1;j++)
			{
			vector<uint64_t> vect_combine_neu1;
		
			vector<uint64_t> vect_combine_neu2;
				
				//show_matrix(vect_combine_neu1, vect_combine_neu1.size());
				//show_matrix(vect_combine_neu2, vect_combine_neu2.size());
				//vec_new_agent[0]=i[0]; //ca
				//vec_new_agent[1]=i[1];//cb
				//vec_new_agent[4]=i[2];//da
				//vec_new_agent[6]=i[3];//db
				//vec_new_agent[3]=j[0];//ec
				//vec_new_agent[7]=j[1];//ed
				//vec_new_agent[2]=j[2];//fc
				//vec_new_agent[5]=j[3];//fd
			
			vect_ca=expand_one_layer(vec_all_combine1[i*4+0], layer_whole_net,neurons_per_layer);
			vect_cb=expand_one_layer(vec_all_combine1[i*4+1], layer_whole_net,neurons_per_layer);
			vect_da=expand_one_layer(vec_all_combine1[j*4+2], layer_whole_net,neurons_per_layer);
			vect_db=expand_one_layer(vec_all_combine1[j*4+0], layer_whole_net,neurons_per_layer);
			vect_ec=expand_one_layer(vec_all_combine1[i*4+2], layer_whole_net,neurons_per_layer);
			vect_ed=expand_one_layer(vec_all_combine1[j*4+3], layer_whole_net,neurons_per_layer);
			vect_fc=expand_one_layer(vec_all_combine1[i*4+3], layer_whole_net,neurons_per_layer);
			vect_fd=expand_one_layer(vec_all_combine1[j*4+1], layer_whole_net,neurons_per_layer);
			
			/*
			cout<<"ca:"<<endl;
			show_matrix(vect_ca, neurons_per_layer);
			cout<<"cb"<<endl;
			show_matrix(vect_cb, neurons_per_layer);
			cout<<"da"<<endl;
			show_matrix(vect_da, neurons_per_layer);
			cout<<"db"<<endl;
			show_matrix(vect_db, neurons_per_layer);
			*/
			
			for (uint64_t k=0;k<neurons_per_layer;k++)	
				{
					for (uint64_t k1=0;k1<neurons_per_layer;k1++)	
					{
						vect_combine_neu1.push_back(vect_ca[k*neurons_per_layer+k1]);
					}
					for (uint64_t k1=0;k1<neurons_per_layer;k1++)	
					{
						vect_combine_neu1.push_back(vect_cb[k*neurons_per_layer+k1]);
					}					
				}
			for (uint64_t k=0;k<neurons_per_layer;k++)	
				{
					for (uint64_t k1=0;k1<neurons_per_layer;k1++)	
					{
						vect_combine_neu1.push_back(vect_da[k*neurons_per_layer+k1]);
					}
					for (uint64_t k1=0;k1<neurons_per_layer;k1++)	
					{
						vect_combine_neu1.push_back(vect_db[k*neurons_per_layer+k1]);
					}					
				}
			
			
			
				
			for (uint64_t k=0;k<neurons_per_layer;k++)	
				{
					for (uint64_t k1=0;k1<neurons_per_layer;k1++)	
					{
						vect_combine_neu2.push_back(vect_ec[k*neurons_per_layer+k1]);
					}
					for (uint64_t k1=0;k1<neurons_per_layer;k1++)	
					{
						vect_combine_neu2.push_back(vect_ed[k*neurons_per_layer+k1]);
					}					
				}	
			for (uint64_t k=0;k<neurons_per_layer;k++)	
				{
					for (uint64_t k1=0;k1<neurons_per_layer;k1++)	
					{
						vect_combine_neu2.push_back(vect_fc[k*neurons_per_layer+k1]);
					}
					for (uint64_t k1=0;k1<neurons_per_layer;k1++)	
					{
						vect_combine_neu2.push_back(vect_fd[k*neurons_per_layer+k1]);
					}					
				}
				/*
				//count(vect_combine_neu1, vect_combine_neu1.size())
				cout<<"vect_combine_neu1"<<endl;
				show_matrix(vect_combine_neu1, neurons_per_layer*2);
				cout<<"ec"<<endl;
				show_matrix(vect_ec, neurons_per_layer);
				cout<<"ed"<<endl;
				show_matrix(vect_ed, neurons_per_layer);
				cout<<"fc"<<endl;
				show_matrix(vect_fc, neurons_per_layer);
				cout<<"fd"<<endl;
				show_matrix(vect_fd, neurons_per_layer);
				cout<<"vect_combine_neu2"<<endl;
				show_matrix(vect_combine_neu2, neurons_per_layer*2);
				//count(vect_combine_neu2, vect_combine_neu2.size())
				*/
				outf5<<count(vect_combine_neu1, vect_combine_neu1.size())<<"*"<<count(vect_combine_neu2, vect_combine_neu2.size())<<endl;		
				//cout<<count(vect_combine_neu1, vect_combine_neu1.size())<<"*"<<count(vect_combine_neu2, vect_combine_neu2.size())<<endl;	
				//cout<<"finish"<<endl;
			}
		}
	outf5.close();
	
	
}
			

