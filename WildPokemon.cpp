#include "WildPokemon.h"

WildPokemon::WildPokemon(unsigned int id, Point2D in_loc):GameObject(in_loc, id, 'W') {
    this->id_num = id;
    this->location = in_loc;
    this->startingLoc = location;
    speed = 3;
}

WildPokemon::WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc):GameObject(in_loc, id, 'W') {
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    this->id_num = id;
    this->location = in_loc;
    this->startingLoc = in_loc;
    speed = 3;
}
void WildPokemon::follow(Trainer* t) { //need to update trainer information aswell
    current_trainer = t;
    state = IN_TRAINER;
    cout << this->display_code << this->id_num << " (" << this->name << ") is following " << t->GetDisplayCode() << t->GetId() << " (" << t->GetName() << ")";
}
bool WildPokemon::get_variant() {
    return variant; 
}
double WildPokemon::get_attack() {
    return attack;
}
double WildPokemon::get_health() {
    return health;
}
bool WildPokemon::get_in_combat() {
    return in_combat;
}
//start following trainer
//Check if there is a trainer within x spaces,
//if there is, it will follow
//some pmon will be faster than trainer, so it will catch up .
//if mon walks into gym, pmon will go back to default location maybe??
//possibly have a despawn and return to set area/main spot for x amount of ticks
//think having it walk back will be jank and doesnt make sense
//add legendary pokemon with status effects (lower speed, teleportation like abra from smash bros????)
    
bool WildPokemon::Update() {
    if(!IsAlive()) {
        state = DEAD;
    }
    switch (state)
    {
    case IN_ENVIRONMENT:
        Vector2D dist = destination - location;
        dist.x = fabs(dist.x);
        dist.y = fabs(dist.y);
        if(dist.x <= fabs(delta.x) && dist.y <= fabs(delta.y)) {
            location = destination;
            
        }
        else {
            location = location + delta;
        }
        
        break;
    case DEAD:
        break;
    case IN_TRAINER:
        if(current_trainer->GetState() == IN_GYM || current_trainer->GetState() == AT_CENTER) {
            state = IN_ENVIRONMENT;
            destination = startingLoc;
            delta = (destination - this->location) / (GetDistanceBetween(destination, this->location));
            break;
        }
        else{
            delta = (current_trainer->GetLocation()- this->location) * (this->speed) / (GetDistanceBetween(current_trainer->GetLocation(), this->location));
        }
        location = location + delta;
        
    default:
        break;
    }
}


double WildPokemon::GetProximity() {
    return proximity;
}

void WildPokemon::ShowStatus() {
    cout << "Wild Pokemon status: ";
    GameObject::ShowStatus();
    switch (state)
    {
    case IN_ENVIRONMENT:
        cout << "The WildPokemon is in the environment" << endl;
        break;
    case DEAD:
        cout <<"The WildPokemon is dead" << endl;
    case IN_TRAINER:
        cout << "The WildPokemon is following " << current_trainer->GetName() << endl;
    default:
        break;
    }
}
bool WildPokemon::IsAlive() {
    if(this->health > 0) {
        return true;
    }
    return false;
}

bool WildPokemon::ShouldBeVisible() {
    if(IsAlive()) {
        return true;
    }
    return false;
}