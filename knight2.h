#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"
class BaseKnight;
class BaseItem;
class Events;
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum ItemType { ANTIDOTE , PHOENIXI , PHOENIXII , PHOENIXIII ,PHOENIXIV };


class itemlist{
	public:
		BaseItem *item;
		itemlist *next;
		
		itemlist(){};
		~itemlist();
		static itemlist * create(BaseItem *x)
		{
			itemlist *p = new itemlist();
			p->item = x;
			p->next = nullptr;
			return p;
		}		
};

//...........................................................checking knight type.............................................................///

class BaseBag {
protected:
	itemlist *head ;
	BaseKnight *knight;
	int numberofitem;
public:
	BaseBag(BaseKnight *hiepsi , int phoenixdown , int antidote);
	~BaseBag();
    virtual bool insertFirst(BaseItem * item){};      //DONE
    virtual BaseItem * get(ItemType itemType);        // SIGNALFAULT
    virtual string toString()const;                          //DONE
    virtual bool checkingitem(ItemType x);
    virtual void xoaphantudau();
    virtual bool checkingvoid();
};
class BaseOpponent{
	protected:
		int basedamge;
		int gil;
		int levelO;
	public:
		virtual bool fight(BaseKnight *knight) = 0;
};

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
	BaseKnight(){
		bag = nullptr;
	}
	~BaseKnight(){
		delete bag;
	}
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    int getlevel(){  return level;}
    int gethp()  {return hp;}
    int getgil() {return gil;}
    void gilchange(int GIL) { gil = GIL ;}
	int getmaxhp(){  return maxhp;}
	void hpchange(int HP) {	hp=HP;}
	void uplevel(int LV) { level = LV;}
	KnightType getknight(){ return knightType; }
	BaseBag *getbag(){return bag;}
	void usingphoenixdown(int type)
	{
		if(type == 1 || type == 2) hp=maxhp;
		if(type == 3)
		{
			if(hp <= 0) hp = maxhp/3;
			else hp+= maxhp/4;
		}
		if(type == 4)
		{
			if(hp <= 0) hp = maxhp/2;
			else hp+= maxhp/5;
		}
	}
};

class ArmyKnights {
private:
	BaseKnight **knight;
	int numberofknight;
	bool PaladinShield;
	bool LancelotSpear;
	bool GuinevereHair;
	bool ExcaliburSword;
public:
    ArmyKnights (const string & file_armyknights)
    {
    	ifstream f(file_armyknights);
    	int n;
    	f>>n;
    	knight = new BaseKnight*[n];   // cap phat vung nho cho n hiep si
    	numberofknight = n;
		for(int i= 0 ; i< n; i++)
		{
			int id,maxhp,level,gil,antidote,phoenixdownI;
			KnightType knightType;
			knight[i] = new BaseKnight;   // cap phat vung nho cho hiep si thu i
			id = i+1 ;
			f>>maxhp>>level>>phoenixdownI>>gil>>antidote;
			knight[i] = BaseKnight::create( id , maxhp , level , gil , antidote , phoenixdownI);
		}
		PaladinShield = false;
		LancelotSpear = false;
		GuinevereHair = false;
		ExcaliburSword = false;
		f.close();
	}
    ~ArmyKnights()
    {
    	for(int i = 0;i< numberofknight;i++) delete knight[i];
    	
		delete knight;
	}
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const{
    	return numberofknight;
	}
    
    BaseKnight * lastKnight() const{
    	if(numberofknight == 0) return nullptr;
    	return knight[numberofknight -1];
	};

    bool hasPaladinShield() const{ return PaladinShield; };
    bool hasLancelotSpear() const{ return LancelotSpear;};
    bool hasGuinevereHair() const{ return GuinevereHair;};
    bool hasExcaliburSword() const{ return ExcaliburSword;};

    void printInfo() const;
    void printResult(bool win) const;
    bool hprestore(BaseKnight *knight);
};

class BaseItem {
public:
	ItemType type;
	~BaseItem(){};
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};
class Antidote : public BaseItem{
	public:
		Antidote() {   type = ANTIDOTE; }
		bool canUse(BaseKnight * knight){
			return true;
		}
		void use(BaseKnight * knight){
		}
};
class PhoenixDownI : public BaseItem{
	public:
		PhoenixDownI(){
			type = PHOENIXI;
		}
		bool canUse(BaseKnight * knight)
		{
			int hp = knight->gethp();
			if( hp <= 0 ) return true;
			return false; 
		}
		void use(BaseKnight * knight)
		{
			knight->usingphoenixdown(1);
		}
};
class PhoenixDownII : public BaseItem{
	public:
		PhoenixDownII(){
			type = PHOENIXII;
		}
		bool canUse(BaseKnight * knight)
		{
			int hp = knight->gethp();
			int maxhp= knight->getmaxhp();
			if( hp < maxhp/4 ) return true;
			return false;
		}
		void use(BaseKnight * knight)
		{
			knight->usingphoenixdown(2);
		}
};
class PhoenixDownIII : public BaseItem{
	public:
		PhoenixDownIII(){
			type = PHOENIXIII;
		}
		bool canUse(BaseKnight * knight)
		{
			int hp = knight->gethp();
			int maxhp= knight->getmaxhp();
			if( hp < (maxhp)/3 ) return true;
			return false;
		}
		void use(BaseKnight * knight)
		{
			knight->usingphoenixdown(3);
		}
};
class PhoenixDownIV : public BaseItem{
	public:
		PhoenixDownIV(){
			type = PHOENIXIV;
		}
		bool canUse(BaseKnight * knight)
		{
			int hp = knight->gethp();
			int maxhp= knight->getmaxhp();
			if( hp < (maxhp)/2 ) return true;
			return false;
		}
		void use(BaseKnight * knight)
		{
			knight->usingphoenixdown(4);
		}
};


class Events {
private:
	int numberevent;
	int *evts = nullptr; 
public:
	Events(const string &filename)
	{
		ifstream f(filename);
		f>>numberevent;
		evts= new int[numberevent + 1];
		for(int i = 1 ; i <= numberevent ;i++ )
		{
			f>>evts[i];
		}
		f.close();
	}
	~Events()
	{
		delete evts;	
	}
    int count() const
	{
		return numberevent;
	}
    int get(int i) const
	{
		return evts[i];
	}
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__
