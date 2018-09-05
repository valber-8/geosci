#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
#include <sys/time.h>
#include <algorithm>
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

std::vector<uint64_t> Full_arrangement(uint64_t neurons_per_layer) {
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
	std::vector<uint64_t> order1(neurons_per_layer);
	std::vector<uint64_t> order2(neurons_per_layer);
	std::vector<uint64_t> change(2);
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

int main(int argc, char* argv[]) {
	
	uint64_t n_whole_net;
	uint64_t layer_whole_net;
	uint64_t neurons_per_layer;
	uint64_t h;	
	//n_whole_net=138995;
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
	//cout<<count<<endl;
	
	
	
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
	
	ofstream outf; 
	uint64_t new_n_whole_net;
	
	outf.open("abcd.txt");	
	for (uint64_t i=0;i<power_self(h);i++)
	
	//for (uint64_t i=1;i<2;i++)
		{
			uint64_t n_matrix;		
			if (fit_check(i, layer_whole_net, neurons_per_layer)>0)
			{						
			new_n_whole_net=min_reformation(i,layer_whole_net, neurons_per_layer);
			
			outf<<new_n_whole_net<<"*"<<i<<endl;
			}		
		}
	outf.close();	
	//cout<<count<<endl;
	
	*/
	
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
	
	
}
