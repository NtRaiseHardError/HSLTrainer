#include <Windows.h>

#include "Trainer.h"

// initialise trainer instance
Trainer *Trainer::t_instance = 0;

/*
 * Initialise the base address and obtain the 
 * address of the player struct. Default disable
 * godmode.
 *
 * Note that we must start a new game before 
 * applying any h4x otherwise the address will
 * not contain a valid player struct.
 */
Trainer::Trainer() {
	// player struct at 00BA6140
	this->baseAddress = reinterpret_cast<unsigned int>(::GetModuleHandle(TEXT("HackSlashLoot.exe")));
	this->p = reinterpret_cast<player *>(*reinterpret_cast<unsigned int *>(this->baseAddress + ADDR_OFFSET_PLAYER_STRUCT));
	this->isGodmode = false;
}

Trainer::~Trainer() {
}

/*
 * Return the existing instance of the Trainer
 */
Trainer * Trainer::instance() {
	if (!t_instance)
		t_instance = new Trainer();
	return t_instance;
}

/*
 * In case we retrieve the player struct 
 * before starting a new game.
 */
void Trainer::Reset() {
	this->p = reinterpret_cast<player *>(*reinterpret_cast<unsigned int *>(this->baseAddress + ADDR_OFFSET_PLAYER_STRUCT));
}

/*
 * Change the health of the player.
 * Param : new health
 */
void Trainer::ModifyHealth(int health) {
	this->p->health = health;
}

/*
 * Change the player's base armour.
 * Param : new armour
 */
void Trainer::ModifyArmour(int armour) {
	this->p->baseArmour = armour;
}

/*
 * Change the attack (accuracy) value.
 * Param : type of attack
 * Param : new attack value
 */
void Trainer::ModifyAttack(int type, int attack) {
	if (type == Trainer::MELEE)
		this->p->baseMeleeAttack = attack;
	else if (type == Trainer::RANGED)
		this->p->baseRangedAttack = attack;
	else if (type == Trainer::MAGIC)
		this->p->baseMagicAttack = attack;
}

/*
* Change the damage value.
* Param : type of damage
* Param : new damage value
*/
void Trainer::ModifyDamage(int type, int damage) {
	if (type == Trainer::MELEE)
		this->p->baseMeleeDamage = damage;
	else if (type == Trainer::RANGED)
		this->p->baseRangedDamage = damage;
	else if (type == Trainer::MAGIC)
		this->p->baseMagicDamage = damage;
}

/*
 * Enables or disables godmode.
 * Param : true to enable, false to disable
 */
void Trainer::EnableGodmode(bool enable) {
	this->isGodmode = enable;
	void *takeDamageAddr = reinterpret_cast<void *>(this->baseAddress + ADDR_OFFSET_SUBTRACT_HEALTH);
	DWORD flOldProtect = 0;
	::VirtualProtect(takeDamageAddr, 3, PAGE_EXECUTE_READWRITE, &flOldProtect);
	if (this->isGodmode) {
		*reinterpret_cast<unsigned char *>(takeDamageAddr) = 0x90;
		*(reinterpret_cast<unsigned char *>(takeDamageAddr) + 1) = 0x90;
		*(reinterpret_cast<unsigned char *>(takeDamageAddr) + 2) = 0x90;
	} else {
		*reinterpret_cast<unsigned char *>(takeDamageAddr) = 0x29;
		*(reinterpret_cast<unsigned char *>(takeDamageAddr) + 1) = 0x43;
		*(reinterpret_cast<unsigned char *>(takeDamageAddr) + 2) = 0x50;
	}
	::VirtualProtect(takeDamageAddr, 3, flOldProtect, &flOldProtect);
}

/*
 * Returns true if godmode is enabled, otherwise false.
 */
bool Trainer::IsGodmode() {
	return this->isGodmode;
}