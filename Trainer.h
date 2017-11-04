#pragma once
#ifndef __TRAINER_H__
#define __TRAINER_H__

#define ADDR_OFFSET_PLAYER_STRUCT 0x7A6140
#define ADDR_OFFSET_SUBTRACT_HEALTH 0x147D6E

typedef struct _player {
	void *unknown1;
	int unknown2;
	void *unknown3;
	void *unknown4;
	int unknown5;
	int unknown6;
	int unknown7;
	int unknown8;
	int unknown9;
	void *unknown10;
	int unknown11;
	unsigned int faceDirection;	// 1 (right) or 0xFFFFFFFF (left)
	int unknown12;
	int baseMeleeAttack;	// accuracy
	int baseRangedAttack;
	int baseMagicAttack;
	int baseArmour;
	int baseMeleeDamage;
	int baseRangedDamage;
	int baseMagicDamage;
	int health;
	int resistance;
	int vulnerability;
	int unknown14;
} player;

class Trainer {
	private:
	unsigned int baseAddress;
	player *p;
	bool isGodmode;
	static Trainer *t_instance;

	Trainer();
	~Trainer();
	Trainer(Trainer& other) {}
	Trainer& operator=(Trainer& other) {}

	public:
	static const int MELEE = 0;
	static const int RANGED = 1;
	static const int MAGIC = 2;
	static Trainer *instance();
	void Reset();
	void ModifyHealth(int health);
	void EnableGodmode(bool enable);
	void ModifyArmour(int armour);
	void ModifyAttack(int type, int attack);
	void ModifyDamage(int type, int damage);
	bool IsGodmode();
};

#endif // !__TRAINER_H__

