#include "airport_manager.h"

void main(){}

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
        return 0;
}

//part5
int PrintFlightsFromAirport(Airline *airline, const char *origin_name){
    return 0;
}

//part6
int PrintFlightsToAirport(Airline *airline, const char *dest_name){
    return 0;
}

//part7
void PrintAirlineAsMatrix(Airline *airline){

}

//part8
int HasDirectFlight(Airline *airline, const char *origin_name, const char *dest_name){
    return 0;
}

//part9
int HasOneStopFlight(Airline *airline, const char *origin_name, const char *dest_name){
    return 0;
}

//part10
void DeleteAirline(Airline *airline){
    
}

//EC
void GuaranteeOneStop(Airline *airline){
    
}



