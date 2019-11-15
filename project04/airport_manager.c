#include "airport_manager.h"

//void main(){}

//part 1
void InitializeAirline(Airline *airline, int maxAirportsN){
    airline->airports = (Airport**)malloc(sizeof(Airport) * maxAirportsN);
    airline->numAirports = 0;
    airline->maxAirports = maxAirportsN;
}

//part2
int AddAirport(Airline *airline, const char* name){ 
    char* portname = (char*)malloc((sizeof(char) * strlen(name)) + 1);
    strcpy(portname, name);

    //airport not yet part of airline
    if(FindAirport(airline, name) == NULL){ 
        Airport* port = (Airport*)malloc(sizeof(Airport));
        port->name = portname;
        port->numDestinations = 0;
        port->destinations = NULL;
        if(airline->numAirports >= airline->maxAirports){
             airline->maxAirports*=2;
            airline->airports = (Airport**)realloc(airline->airports, sizeof(Airport) * airline->maxAirports);
        }
        airline->airports[airline->numAirports] = port;
        airline->numAirports++;
        return 1;
    } 

    //airport already part of airline
    else {
        free(portname);
        return 0;
    }
}

//part3
Airport *FindAirport(Airline *airline, const char *name){
    //Airline *temp = airline;
    int numPorts = airline->numAirports;

    for(int i = 0; i<numPorts; i++){
        if(strcmp(airline->airports[i]->name, name) == 0){
            return airline->airports[i];
        }
    }
    return NULL;
}

//part4
int AddFlight(Airline *airline, const char* origin_name, const char* dest_name){ 
    int numPorts = airline->numAirports;
    int found = 0;
    for(int i = 0; i<numPorts; i++){
        if(strcmp(airline->airports[i]->name, origin_name) == 0){
            for(int j = 0; j<airline->airports[i]->numDestinations; j++){
                if(strcmp(airline->airports[i]->destinations[j]->name, dest_name) == 0){
                    found = 1;
                }
            }
        }
    }

    if(FindAirport(airline, origin_name) == NULL ||  
    FindAirport(airline, dest_name) == NULL ||
    strcmp(origin_name, dest_name) == 0 ||
    found == 1
    ){
        return 0;
    }
    else{
        Airport* oport = FindAirport(airline, origin_name);
        Airport* dport = FindAirport(airline, dest_name);
        int x = (oport->numDestinations + 1); //create space for 1 more destination
        oport->destinations = (Airport**)realloc(oport->destinations, sizeof(Airport) * x);
        oport->destinations[x-1] = dport;
        oport->numDestinations++;
        return 1;
    }
}

//part5
int PrintFlightsFromAirport(Airline *airline, const char *origin_name){
    Airport* oport = FindAirport(airline, origin_name);
    if(FindAirport(airline, origin_name) == NULL){
        return 0;
    }
    else{
    for(int i = 0; i<oport->numDestinations; i++){
    printf("%s\n", oport->destinations[i]->name);
    }
    return 1;
    }
}

//part6
int PrintFlightsToAirport(Airline *airline, const char *dest_name){
    if(FindAirport(airline, dest_name) == NULL){
        return 0;
    }
    else{
    for(int j = 0; j<airline->numAirports; j++){
        for (int i = 0; i < airline->airports[j]->numDestinations; i++){
            if(strcmp(airline->airports[j]->destinations[i]->name, dest_name) == 0){
                printf("%s\n", airline->airports[j]->name);
            }
        }
    }
    return 1;
    }
}

//part7
void PrintAirlineAsMatrix(Airline *airline){
    for (int i = 0; i < airline->numAirports; i++)
    {
        for (int j = 0; j<airline->numAirports; j++)
        {
            printf("%d", HasDirectFlight(airline, airline->airports[i]->name, airline->airports[j]->name));
        }
        printf("\n");
    }
}

//part8
int HasDirectFlight(Airline *airline, const char *origin_name, const char *dest_name){
    if(FindAirport(airline, origin_name) == NULL ||  
    FindAirport(airline, dest_name) == NULL ||
    strcmp(origin_name, dest_name) == 0){
        return 0;
    }

    for (int i = 0; i < airline->numAirports; i++){
        if(strcmp(airline->airports[i]->name, origin_name) == 0)
        for (int j = 0; j < airline->airports[i]->numDestinations; j++){
            if(strcmp(airline->airports[i]->destinations[j]->name, dest_name) == 0){
                return 1;
            }
        }
    }
    return 0;
}

//part9
int HasOneStopFlight(Airline *airline, const char *origin_name, const char *dest_name){
    if(FindAirport(airline, origin_name) == NULL ||  
    FindAirport(airline, dest_name) == NULL ||
    strcmp(origin_name, dest_name) == 0){
        return 0;
    }

    for (int i = 0; i < airline->numAirports; i++){
        if(strcmp(airline->airports[i]->name, origin_name) == 0){
        for (int j = 0; j < airline->airports[i]->numDestinations; j++){
            for(int k = 0; k<airline->airports[i]->destinations[j]->numDestinations; k++){
                if(strcmp(airline->airports[i]->destinations[j]->destinations[k]->name, dest_name) == 0){
                return 1;
                    }
                }
            }
        }
    }
   return 0;
}

//part10
void DeleteAirline(Airline *airline){
    for (int i = 0; i < airline->numAirports; i++){
        free(airline->airports[i]->name);  
        free(airline->airports[i]->destinations);
        free(airline -> airports[i]);
    }
    free(airline->airports);
}

//EC
void GuaranteeOneStop(Airline *airline){
    for(int i = 0; i<airline->numAirports; i++){//single airports 
            for(int c = 0; c<airline->numAirports; c++){
                AddFlight(airline, airline->airports[i]->name, airline->airports[c]->name);
        }
    }
}



