#include <iostream>
#include<math.h>
#include <fstream>
#include<vector>
#include <algorithm>

using namespace std;
#include <cstdlib>

///////skill////////////////////
class skill{
	public:
    	string name;
    	int level;
    	
    		
    		skill(int level,string name)
    		{
    			this->name=name;
				this->level=level;
			}
			
	
	};

//////////contributor/////////////////////////
  class contributor{
  	   public:
  	   	 bool disponibilite;
        string name;
        vector<skill> skills;
        
     contributor(){disponibilite=true;}
            contributor(string name)
            {
            	disponibilite=false;
            	this->name=name;
			}
			
			void ajoute_skill(skill s)
			{
				skills.push_back(s);
			}

   		 static bool compareCpusByValue(skill s,contributor &a, contributor &b) {
   		 	int ax,bx;
   		 		for(int i=0;i<a.skills.size();i++)
   		 		{  
					 if(s.name==a.skills[i].name)
					 ax=a.skills[i].level;
					}
					for(int i=0;i<b.skills.size();i++)
   		 		{  
					 if(s.name==b.skills[i].name)
					 bx=b.skills[i].level;
					}
        return ax<bx;
    }
    
   
    };
   
   ////list of contributor/////////////////////
   
class contributors{
		public:
	vector<contributor> contributors;
	

		void ajoute_ctr(contributor c)
		{
			contributors.push_back(c);
		}
		
		         	void sorti(skill s)
	{
	    for(int i=0;i<contributors.size()-1;i++)
	    {
	    	if(contributor::compareCpusByValue(s,contributors[i],contributors[i+1])) 
	    	{
	    		contributor c;
	    		c=contributors[i+1];
	    		contributors[i+1]=contributors[i];
	    		contributors[i]=c;
			}
		}
		 
    }
	
};
 
    
  //////project/////////////////  
class project{
	public:
    string name;
    int duration;
    int score;
    int BestBefore;
    vector <contributor> list_ctr;
    vector <skill> list_skill;
    int nbr_role;
    
    
    	project(){}
    project(string n,int d,int s,int b,int nbr){

        name=n;
        duration=d;
        score=s;
        BestBefore=b;
        nbr_role=nbr;
      }
    void ajouter_ctr(contributor c)
    {
      list_ctr.push_back(c);
        }
        
        void ajoute_skill(skill s)
        {
        	list_skill.push_back(s);
		}
		
		contributors trier_selon_skill(skill s,contributors cs)
		{
			contributors tab;
			for(int i=0;i<cs.contributors.size();i++)
			{
				for(int j=0;j<cs.contributors[i].skills.size();j++)
				{
				if(s.name==cs.contributors[i].skills[j].name) 
				{
					tab.ajoute_ctr(cs.contributors[i]);
					break;
				}
			    }
			}
			tab.sorti(s);
			return tab;
		}
		
		int score1()
		{
			if(duration<BestBefore) return score;
			else {
				return (score-(duration-BestBefore));
			}
		}
		
		void choisir(contributors cs)
		{
				for(int i=0;i<cs.contributors.size();i++)
				{
				if(cs.contributors[i].disponibilite)
				{
				list_ctr.push_back(cs.contributors[i]);
				break;
			}
		}
		   	
		}
		
		void affecter_ctr1(contributors cs)
		{
			for(int i=0;i<list_skill.size();i++)
			{ contributors t;
				t=trier_selon_skill(list_skill[i],cs);
				list_ctr.push_back(t.contributors[0]);
				
			}
			
			kamel(cs);
			for(int i=0;i<list_ctr.size();i++)
			{
				list_ctr[i].disponibilite=false;
			}
		}
			void affecter_ctr2(contributors cs)
		{
			for(int i=0;i<list_skill.size();i++)
			{contributors t;
				t=trier_selon_skill(list_skill[i],cs);
				for(int i=0;i<t.contributors.size();i++)
				{
				if(t.contributors[i].disponibilite)
				{
				list_ctr.push_back(t.contributors[i]);
				break;
			}
			}
				
			}
				kamel(cs);
			for(int i=0;i<list_ctr.size();i++)
			{
				list_ctr[i].disponibilite=false;
			}
		}
		void kamel(contributors cs)
		{
			if(list_ctr.size()<nbr_role)
			{
			   for(int i=list_ctr.size();i<nbr_role;i++)
			   choisir(cs);	
			}
		}
};




//////////list of projects/////////////////////////
class projects{
		public:
	vector<project> projects;
	

		
		void ajoute_proj(project p)
		{
			projects.push_back(p);
		}
		
		void trier()
		{
			for(int i=0;i<projects.size()-1;i++)
			{
			   if(projects[i].score1()<projects[i].score1())
			  {
			    project p;
			   p=projects[i];
			   projects[i]=projects[i+1];
			   projects[i+1]=p;	
		}
			}
		}
		
		void affectation(contributors cs)
		{
			projects[0].affecter_ctr1(cs);
				for(int i=1;i<projects.size()-1;i++)
				{
					projects[i].affecter_ctr2(cs);
				}
			
		}
};


//////main////////////////////////////
int main()
{   
      contributors ctrs;
      projects prjs;
      
	ifstream indata;
	indata.open("a_an_example.in.txt");
	
	int nbr_contr,nbr_proj;
	indata >>nbr_contr;
	indata >>nbr_proj;
	
	for(int i=0;i<nbr_contr;i++)
	{
		string name_cntr;
		int nbr_skill;
		indata >>name_cntr;
		contributor ctr(name_cntr);
		indata >>nbr_skill;
		
		for(int i=0;i<nbr_skill;i++)
		{
			string name_skill;
			int skill_level;
			indata >>name_skill;
			indata >>skill_level;
			skill s(skill_level,name_skill);
			ctr.ajoute_skill(s);
		}
		ctrs.ajoute_ctr(ctr);
	}
	
	
	
	for(int i=0;i<nbr_proj;i++)
	{
		string name_proj;
		int nbr_day,score,best_before,nbr_role;
		indata>>name_proj;
		indata>>nbr_day;
		indata>>score;
		indata>>best_before;
		indata>>nbr_role;
		
	  project prj(name_proj,nbr_day,score,best_before,nbr_role);
		for(int i=0;i<nbr_role;i++)
		{
			string name_skill;
			int req_skill_level;
			indata>>name_skill;
			indata>>req_skill_level;
			skill s(req_skill_level,name_skill);
			prj.ajoute_skill(s);
		}
		prjs.ajoute_proj(prj);
	}
	
	
	
	prjs.trier();
	prjs.affectation(ctrs);
	
	ofstream out;
	out.open("resultat5.txt");
	
	out<<nbr_proj<<endl;

	for(int i=0;i<prjs.projects.size();i++)
	{   
		out<<prjs.projects[i].name<<endl;
		for(int j=0;j<prjs.projects[i].list_ctr.size();j++)
		{
			out<<prjs.projects[i].list_ctr[j].name<<" ";
		}
		out<<endl;
	}
	
	
	
	
	cout<<0;
	indata.close();
	
	
}
