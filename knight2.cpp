#include "knight2.h"

bool checkingprime(int n){
	if( n < 2) return false;
	if( n == 2) return true;
	for(int i = 2 ; i <=n/2 ; i++)
	{
		if( n%i ==0 ) return false;
	}
	return true;
}
bool checkingpytagoras(int n){
	int *a =new int[4];
	if(n<=99) return false;
	for(int i=1 ;i<=3;i++)
	{
		a[i]=n%10;
		n/=10;
	}
	for(int i = 1; i<=3 ;i++) if(a[i] == 0) return false;
	if( (pow(a[1],2) +pow(a[2],2) ==pow(a[3],2))||(pow(a[2],2) +pow(a[3],2) ==pow(a[1],2))||(pow(a[1],2) +pow(a[3],2) ==pow(a[2],2)) ) return true;
	return false;
}
KnightType checking_knight_class(int HP){
	if(HP==888) return LANCELOT;
	if(checkingprime(HP)) return PALADIN;
	if(checkingpytagoras(HP)) return DRAGON;
	return NORMAL;
}


itemlist::~itemlist(){
	delete item;
}

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag(BaseKnight *hiepsi ,int phoenixdown , int antidote){
	numberofitem = 0;
	head = nullptr;
	knight = hiepsi;
	for(int i= 1;i <=phoenixdown ;i++)
	{
		BaseItem *item;
		itemlist *idem;
		item = new PhoenixDownI;
		idem = itemlist::create(item);
		if(head == nullptr) head = idem;
		else{
			idem->next = head;
			head = idem;
			}
			numberofitem++;	
	}
	if(hiepsi->getknight() != DRAGON)
	{
		for(int i= 0;i <antidote ;i++)
		{
			BaseItem *item;
			itemlist *idem;
			item = new Antidote;
			idem = itemlist::create(item);
			if(head == nullptr) head = idem;
			else{
				idem->next = head;
				head = idem;
			}
			numberofitem++;
		}
	}
}
BaseBag::~BaseBag(){
	while(head != nullptr){
		this->xoaphantudau();
	}
}
BaseItem * BaseBag::get(ItemType itemType){
		bool anti = true;
		if(itemType != ANTIDOTE) anti = false; 
	    itemlist *p = head;
	    while(p!= nullptr && anti == true){
	    	if(p->item->type == itemType && p->item->canUse(knight))
	    	{
	    		BaseItem *tam = head->item;
	    		head->item = p->item;
	    		p->item = tam;
	    		return head->item;
			}
	    	p = p->next;
		}
		while(p!= nullptr && anti == false)
		{
			if(p->item->canUse(knight) && p->item->type != ANTIDOTE){
				BaseItem *tam = head->item;
	    		head->item = p->item;
	    		p->item = tam;
	    		return head->item;
			}
			p = p->next;
		}
		return nullptr;
}
string  BaseBag::toString() const{
	string typeString[5] = {"Antidote", "PhoenixI", "PhoenixII","PhoenixIII", "PhoenixIV"};
    string s("Bag[count=");
    itemlist *p = head;
    s+= to_string(numberofitem);
    s+=";";
    while(p != nullptr){
    	switch (p->item->type)
    	{
    		case (ANTIDOTE) :{
    			s+=typeString[0];
				break;
			}
			 case (PHOENIXI) :{
    			s+=typeString[1];
				break;
			}
			case (PHOENIXII) :{
    			s+=typeString[2];
				break;
			}
			case (PHOENIXIII) :{
    			s+=typeString[3];
				break;
			}
			case (PHOENIXIV) :{
    			s+=typeString[4];
				break;
			}
			default : break;
		}
		p = p->next;
		if(p!= nullptr) s+=",";
	}
	s+="]";
    return s;
}
bool BaseBag::checkingitem(ItemType x){
	itemlist *q= head;
	while(q!= nullptr)
	{
		if(q->item->type == x) return true;
		q = q->next;
	}
	return false;
}
void BaseBag::xoaphantudau(){
	   	if(head != nullptr)
		{
			itemlist *p = head;
			head = head->next;
			delete p;
		}
		numberofitem--;
}
bool BaseBag::checkingvoid(){
	if(head == nullptr) return true;
	return false;
}
class BDragon : public BaseBag{
	public:
		BDragon(BaseKnight *hiepsi ,int phoenixdown , int antidote) : BaseBag::BaseBag( hiepsi , phoenixdown , antidote) {};
		bool insertFirst(BaseItem * item){
			if( numberofitem <14 && item->type != ANTIDOTE)
			{
				itemlist *idem = itemlist::create(item);
				if(head == nullptr) head = idem;
				else{
					idem->next = head;
					head = idem;
				}
				numberofitem++;
				return true;
			}
			return false;
		}
};
class BPaladin : public BaseBag{
	public:
		BPaladin(BaseKnight *hiepsi ,int phoenixdown , int antidote) : BaseBag::BaseBag( hiepsi , phoenixdown , antidote) {};
		bool insertFirst(BaseItem * item){
				itemlist *idem = itemlist::create(item);
				if(head == nullptr) head = idem;
				else{
					idem->next = head;
					head = idem;
				}
				numberofitem++;
			return true;
		}
};
class BLancelot : public BaseBag{
	public:
		BLancelot(BaseKnight *hiepsi ,int phoenixdown , int antidote) : BaseBag::BaseBag( hiepsi , phoenixdown , antidote) {};
		bool insertFirst(BaseItem * item){
			if( numberofitem <16 ) 
			{
				itemlist *idem = itemlist::create(item);
				if(head == nullptr) head = idem;
				else{
					idem->next = head;
					head = idem;
				}
				numberofitem++;
				return true;
			}
			return false;
		}
};
class BNormal : public BaseBag{
	public:
		BNormal(BaseKnight *hiepsi ,int phoenixdown , int antidote) : BaseBag::BaseBag( hiepsi , phoenixdown , antidote) {};
		bool insertFirst(BaseItem * item){
			if( numberofitem < 19 ) 
			{
				itemlist *idem = itemlist::create(item);
				if(head == nullptr) head = idem;
				else{
					idem->next = head;
					head = idem;
				}
				numberofitem++;
				return true;
			}
			return false;
		}
};

/* * * END implementation of class BaseBag * * */
/* * * BEGIN */

/* * * BEGIN implementation of class BaseKnight * * */

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    	BaseKnight *knight = new BaseKnight();
		knight->id = id;
		knight->maxhp  = maxhp;
		knight->hp = maxhp;
		knight->level =  level;
		knight->gil = gil;
		knight->antidote =antidote;
		knight->knightType = checking_knight_class(maxhp);
		switch (knight->knightType)
		{
			case (PALADIN) :
				{
					knight->bag = new BPaladin( knight , phoenixdownI , antidote);
					break;
				}
			case (LANCELOT) :
				{
					knight->bag = new BLancelot( knight , phoenixdownI , antidote);
					break;
				}
			case (DRAGON) :
				{
					knight->bag = new BDragon( knight , phoenixdownI , antidote);
					break;
				}
			case (NORMAL) :
				{
					knight->bag = new BNormal( knight , phoenixdownI , antidote);
					break;
				}
			default : break;
		}
		return knight;
}


string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    string s("");
    
   s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}


/* * * END implementation of class BaseKnight * * */
/* * * BEGIN implementation of class BaseOpponment * * */
class MadBear: public BaseOpponent{
	public:
		MadBear(int i ){
			basedamge = 10;
			gil = 100;
			levelO = (i+1)%10+1;
		}
		bool fight(BaseKnight *knight){   // return true if knight win return false if knight lose...
			if(knight->getlevel() >= levelO ||knight->getknight() == LANCELOT ||knight->getknight() == PALADIN)
			{
				knight->gilchange(knight->getgil() + gil);
				return true;
			}
			int HP= knight->gethp() - basedamge*(levelO - knight->getlevel()) ;
			knight->hpchange(HP);
			return false;
		}
};
class Bandit: public BaseOpponent{
	public:
		Bandit(int i){
			basedamge = 15;
			gil = 150;
			levelO = (i+2)%10+1;
		}
		bool fight(BaseKnight *knight){   // return true if knight win return false if knight lose...
			if(knight->getlevel() >= levelO ||knight->getknight() == LANCELOT ||knight->getknight() == PALADIN) 
			{
				knight->gilchange(knight->getgil() + gil);
				return true;
			}
			int HP= knight->gethp() - basedamge*(levelO - knight->getlevel()) ;
			knight->hpchange(HP);
			return false;
		}
};
class LordLupin: public BaseOpponent{
	public:
		LordLupin(int i){
			basedamge = 45;
			gil = 450;
			levelO = (i+ 3)%10+1;
		}
		bool fight(BaseKnight *knight){   // return true if knight win return false if knight lose...
			if(knight->getlevel() >= levelO ||knight->getknight() == LANCELOT ||knight->getknight() == PALADIN) 
			{
				knight->gilchange(knight->getgil() + gil);
				return true;
			}
			int HP= knight->gethp() - basedamge*(levelO - knight->getlevel()) ;
			knight->hpchange(HP);
			return false;
		}
};
class Elf: public BaseOpponent{
	public:
		Elf(int i ){
			basedamge = 75;
			gil = 750;
			levelO = (i+4)%10+1;
		}
		bool fight(BaseKnight *knight){   // return true if knight win return false if knight lose...
			if(knight->getlevel() >= levelO ||knight->getknight() == LANCELOT ||knight->getknight() == PALADIN)
			{
				knight->gilchange(knight->getgil() + gil);
				return true;
			}
			int HP= knight->gethp() - basedamge*(levelO - knight->getlevel()) ;
			knight->hpchange(HP);
			return false;
		}
};
class Troll: public BaseOpponent{
	public:
		Troll(int i ){
			basedamge = 95;
			gil = 800;
			levelO = (i+5)%10+1;
		}
		bool fight(BaseKnight *knight){   // return true if knight win return false if knight lose...
			if(knight->getlevel() >= levelO ||knight->getknight() == LANCELOT ||knight->getknight() == PALADIN)
			{
				knight->gilchange(knight->getgil() + gil);
				return true;
			}
			int HP= knight->gethp() - basedamge*(levelO - knight->getlevel()) ;
			knight->hpchange(HP);
			return false;
		}
};
class Tornbery:public BaseOpponent{
	public:
	Tornbery(int i){
		levelO = (i+6)%10+1;
	}
	bool fight(BaseKnight *knight){
		if(knight->getlevel() >= levelO) {
			int LV = min(knight->getlevel()+1 , 10);
        	knight->uplevel(LV);
			return true;
		}
		if(knight->getknight() == DRAGON) return true;
		if(knight->getbag()->checkingitem(ANTIDOTE)){
			BaseItem *Antidote = knight->getbag()->get(ANTIDOTE);
			Antidote->use(knight);
			knight->getbag()->xoaphantudau();
			return true;
		}
		else{
			for(int i=1;i<=3 ;i++)
			{
				if(!knight->getbag()->checkingvoid()){    knight->getbag()->xoaphantudau();}
				else break;
			}
			int HP = knight->gethp() -10;
			knight->hpchange(HP);   }
		return false;
	}
};
class Queenofthecard:public BaseOpponent{
	public:
		Queenofthecard(int i){
			levelO = (i+7)%10+1;}
		bool fight(BaseKnight *knight)
		{
			if(knight->getlevel() >= levelO)  return true;
			return false;
		}
};


/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

bool ArmyKnights::fight(BaseOpponent * opponent){
	if(opponent->fight(this->lastKnight())) return true;
	return false;
}
bool ArmyKnights::adventure(Events *events){
	int HPulti = 5000;
	const int MAXGIL = 999;
	const int MAXLV = 10;
	bool OMEGAFOUND = false;
	bool HADESFOUND = false;
	for(int i = 1 ; i<= events->count();i++){
		BaseKnight * lknight = lastKnight();
		if(events->get(i) == 95 && !hasPaladinShield()) PaladinShield = true;
		if(events->get(i) == 96 && !hasLancelotSpear()) LancelotSpear = true;
		if(events->get(i) == 97 && !hasGuinevereHair()) GuinevereHair = true;
		if(events->get(i) == 98 && hasPaladinShield() &&hasLancelotSpear() && hasGuinevereHair()) ExcaliburSword = true;
		if(events->get(i) == 99){
			if(hasExcaliburSword()) 
			{
				this->printInfo();	
				return true;
			}
			if(hasPaladinShield() &&hasLancelotSpear() && hasGuinevereHair()){
				for(int j = numberofknight -1 ;j >= 0; j--)
				{
					int damge;
					if(knight[j]->getknight() == LANCELOT) damge = knight[j]->gethp()* knight[j]->getlevel() * 0.05;
					if(knight[j]->getknight() == PALADIN) damge  = knight[j]->gethp()* knight[j]->getlevel() * 0.06;
					if(knight[j]->getknight() == DRAGON) damge   = knight[j]->gethp()* knight[j]->getlevel() * 0.075;
					if(knight[j]->getknight() == NORMAL) continue;
					HPulti = HPulti - damge;
					if( HPulti > 0)
					{
						for(int shift = j ;shift < numberofknight - 1 ; shift++)
						{
							knight[shift] = knight[shift + 1];
						}
						numberofknight--;
					}
					
					if( HPulti <= 0) break;
				}
                if(HPulti<=0)
				{
					this->printInfo();	
					return true;
				}
				while(this->count())
				{
					delete lknight;
					numberofknight--;
					lknight = lastKnight();
				}
				this->printInfo();	
				return false;
			}
			else{
				while(this->count())
					{
						delete lknight;
						numberofknight--;
						lknight = lastKnight();
					}
				this->printInfo();
				return false;
			}
		}
		if(events->get(i) == 112)
		{
			BaseItem *item = new PhoenixDownII();
			int j = numberofknight;
			for( ; j>0 ;j--)
			{
				BaseKnight *q = knight[j-1];
				if(q->getbag()->insertFirst(item)) break;	
			}
		}
		if(events->get(i) == 113)
		{
			BaseItem *item = new PhoenixDownIII();
			int j = numberofknight;
			for( ; j>0 ;j--)
			{
				BaseKnight *q = knight[j-1];
				if(q->getbag()->insertFirst(item)) break;	
			}
		}
		if(events->get(i) == 114)
		{
			BaseItem *item = new PhoenixDownIV();
			
			int j = numberofknight;
			for( ; j>0 ;j--)
			{
				BaseKnight *q = knight[j-1];
				if(q->getbag()->insertFirst(item)) break;	
			}
		}
        if(events->get(i) == 1){
			BaseOpponent *Madbear = new MadBear(i - 1);
        	if(!fight(Madbear)){
				if(!this->hprestore(lknight)){
				delete lknight;
				numberofknight--;
				lknight = lastKnight();
			}
			}
		}
		if(events->get(i) == 2){
			BaseOpponent *Bandt = new Bandit(i - 1);
        	if(!fight(Bandt)){
				if(!this->hprestore(lknight)){
				delete lknight;
				numberofknight--;
				lknight = lastKnight();
			}
			}
		}
		if(events->get(i) == 3){
			BaseOpponent *lupin = new LordLupin(i - 1);
        	if(!fight(lupin)){
				if(!this->hprestore(lknight)){
				delete lknight;
				numberofknight--;
				lknight = lastKnight();
			}
			}
		}
		if(events->get(i) == 4){
			BaseOpponent *elf = new Elf(i - 1);
        	if(!fight(elf)){
				if(!this->hprestore(lknight)){
				delete lknight;
				numberofknight--;
				lknight = lastKnight();
				}
			}
		}
		if(events->get(i) == 5){
			BaseOpponent *troll = new Troll(i - 1);
        	if(!fight(troll)){
				if(!this->hprestore(lknight)){
				delete lknight;
				numberofknight--;
				lknight = lastKnight();
				}
			}	
		}
		if(events->get(i) == 6){
				BaseOpponent *tornbery = new Tornbery(i - 1);
        		if(!fight(tornbery)){
					if(!this->hprestore(lknight)){
						delete lknight;
						numberofknight--;
						lknight = lastKnight();
					}
				}
		}
		if(events->get(i) == 7){
			BaseOpponent *queen = new Queenofthecard(i - 1);
			if(fight(queen)){
				int GL = 2*lknight->getgil();
				lknight->gilchange(GL);
			}
			else{
				if(lknight->getknight() != PALADIN){
					int GL = (lknight->getgil())/2;
					lknight->gilchange(GL);
				}
			}
		}
		if(events->get(i)==8){
			if(lknight->getknight() != PALADIN)
			{
				if(lknight->getgil() >= 50)
				{
					if(lknight->gethp() < (lknight->getmaxhp())/3){
						int HP = lknight->gethp() + (lknight->getmaxhp())/5;
						int GL = lknight->getgil() -50;
						lknight->hpchange(HP);
						lknight->gilchange(GL);
					}
				}
			}
			else{
				if(lknight->gethp() < (lknight->getmaxhp())/3){
				int HP = lknight->gethp() + (lknight->getmaxhp())/5;
				lknight->hpchange(HP);
				}
			}
		}
		if(events->get(i)==9) lknight->hpchange(lknight->getmaxhp());
		if(events->get(i)==10){
			if(OMEGAFOUND == false)
			{
				if(lknight->getknight() == DRAGON)
				{
					lknight->uplevel(MAXLV);
					lknight->gilchange(MAXGIL);
					OMEGAFOUND = true;
				}
				if(lknight->getlevel() == MAXLV && lknight->gethp() == lknight->getmaxhp())
				{
					lknight->gilchange(MAXGIL);
					OMEGAFOUND = true;
				}
				else{
					lknight->hpchange(0);
					if(!this->hprestore(lknight)) 
					{
						delete lknight;
						numberofknight--;
						lknight = lastKnight();
					}
				}
			}
			if(numberofknight == 0){
				this->printInfo();	
					return false;
			}
		}
		if(events->get(i) == 11){
			if(HADESFOUND == false)
			{
				if((lknight->getknight() == PALADIN && lknight->getlevel() >=8) || (lknight->getlevel() == MAXLV)){
					PaladinShield = true;
					HADESFOUND = true;
				}
				else{
					int HP = 0;
					lknight->hpchange(HP);
					if(!this->hprestore(lknight)) 
					{
						delete lknight;
						numberofknight--;
						lknight = lastKnight();
					}
				}
			}
			if(numberofknight == 0){
				this->printInfo();	
					return false;
			}
		}
		if(this->count() == 0)
		{
			this->printInfo();
			return false;
		}
		if(lknight->getgil() > MAXGIL)
		{
			int GL = lknight->getgil() - MAXGIL;
			lknight->gilchange(MAXGIL);
			int i = this->count() -1;
			for( ;i>=0 ;i--)
			{
				int tiendu = MAXGIL - knight[i]->getgil();
				if(tiendu < GL){
					GL-= tiendu;
					knight[i]->gilchange(MAXGIL);
				}
				else{
					knight[i]->gilchange(knight[i]->getgil() + GL);
					break;
				}
			}
		}
		this->printInfo();
	}	
    return true;
}
bool ArmyKnights::hprestore(BaseKnight *knight){
	BaseKnight *lknight = knight;
	if(lknight->gethp() <= 0)
		{
			BaseItem * phoenixd = lknight->getbag()->get(PHOENIXI);
			if(phoenixd != nullptr){
				phoenixd->use(lknight);
				lknight->getbag()->xoaphantudau();
				if(lknight->gethp() > 0) return true;
			}
			if(lknight->getgil() >= 100){
					int GL = lknight->getgil() -100;
					lknight->gilchange(GL);
					int HP = lknight->getmaxhp() /2;
					lknight->hpchange(HP);
					if(lknight->gethp() <= 0) return false;
					return true;
				}
			else return false;
		}
		if(lknight->gethp() <lknight->getmaxhp())
		{
			BaseItem * phoenixd = lknight->getbag()->get(PHOENIXI);
			if(phoenixd != nullptr){
				phoenixd->use(lknight);
				lknight->getbag()->xoaphantudau();
			}
		}
		return true;
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string &filename){
	armyKnights = new ArmyKnights( filename );
}

void KnightAdventure::loadEvents(const string &filename){
	events = new Events( filename );
}
void KnightAdventure::run(){
	armyKnights->printResult(armyKnights->adventure (events));
}
KnightAdventure::~KnightAdventure(){
	delete armyKnights;
	delete events;
}
/* * * END implementation of class KnightAdventure * * */
/*int main(int argc, char ** argv) {
//	freopen ("outputfile","w",stdout);
    string file_armyknights, file_events;
    if (argc == 1) {
        file_armyknights = "tc1_armyknights"; // hard-code
        file_events = "tc1_events";
    }
    else if (argc == 3) {
        file_armyknights = argv[1];
        file_events = argv[2];
    }
    else {
        cout << "Error number of arguments" << endl;
        exit(1);
    }    
    // BEBGIN
    KnightAdventure * knightAdventure = new KnightAdventure();
	knightAdventure->loadArmyKnights("tc1_armyknights");
    knightAdventure->loadEvents("tc1_events");
    knightAdventure->run();

    delete knightAdventure;
    return 0;
}*/
