default: Ass5

Ass5: main.o PoliticalSys.o Party.o DemocraticParty.o RepublicanParty.o Politician.o DemocratPolitician.o RepublicanPolitician.o LeaderPolitician.o SocialPolitician.o \
	DemocratPoliticianLeader.o DemocratPoliticianSocial.o RepublicanPoliticianLeader.o RepublicanPoliticianSocial.o
	g++ -o Ass5 main.o PoliticalSys.o Party.o DemocraticParty.o RepublicanParty.o Politician.o DemocratPolitician.o RepublicanPolitician.o LeaderPolitician.o SocialPolitician.o \
	DemocratPoliticianLeader.o DemocratPoliticianSocial.o RepublicanPoliticianLeader.o RepublicanPoliticianSocial.o

main.o: main.cpp PoliticalSys.h 
	g++ -g -c main.cpp

PoliticalSys.o: PoliticalSys.cpp PoliticalSys.h RepublicanPoliticianLeader.h RepublicanPoliticianSocial.h DemocratPoliticianLeader.h DemocratPoliticianSocial.h
	g++ -g -c PoliticalSys.cpp
   
Party.o: Party.cpp Party.h Politician.h Defs.h
	g++ -g -c Party.cpp

DemocraticParty.o: DemocraticParty.cpp DemocraticParty.h Party.h
	g++ -g -c DemocraticParty.cpp

RepublicanParty.o: RepublicanParty.cpp RepublicanParty.h Party.h
	g++ -g -c RepublicanParty.cpp

Politician.o: Politician.cpp Politician.h Party.h
	g++ -g -c Politician.cpp

DemocratPolitician.o: DemocratPolitician.cpp DemocratPolitician.h Politician.h
	g++ -g -c DemocratPolitician.cpp

RepublicanPolitician.o: RepublicanPolitician.cpp RepublicanPolitician.h Politician.h
	g++ -g -c RepublicanPolitician.cpp

LeaderPolitician.o: LeaderPolitician.cpp LeaderPolitician.h Politician.h
	g++ -g -c LeaderPolitician.cpp

SocialPolitician.o: SocialPolitician.cpp SocialPolitician.h Politician.h
	g++ -g -c SocialPolitician.cpp

DemocratPoliticianLeader.o: DemocratPoliticianLeader.cpp DemocratPoliticianLeader.h DemocratPolitician.h LeaderPolitician.h
	g++ -g -c DemocratPoliticianLeader.cpp

DemocratPoliticianSocial.o: DemocratPoliticianSocial.cpp DemocratPoliticianSocial.h DemocratPolitician.h SocialPolitician.h
	g++ -g -c DemocratPoliticianSocial.cpp

RepublicanPoliticianLeader.o: RepublicanPoliticianLeader.cpp RepublicanPoliticianLeader.h RepublicanPolitician.h LeaderPolitician.h
	g++ -g -c RepublicanPoliticianLeader.cpp

RepublicanPoliticianSocial.o: RepublicanPoliticianSocial.cpp RepublicanPoliticianSocial.h RepublicanPolitician.h SocialPolitician.h
	g++ -g -c RepublicanPoliticianSocial.cpp

clean:
	rm -f *.o
	rm -f Ass5