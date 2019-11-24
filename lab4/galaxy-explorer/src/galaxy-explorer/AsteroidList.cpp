#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	//intuitively, id like this to make a pointer to an asteroid and throw that into the data entry but
        //it would probably be best to just keep it null to avoid problems with the head node
        this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
	this->data = new Asteroid(a);//a.getID(), a.getMass(), a.getHealth(), a.getCurrentHitbox(), a.getVelocity()); dont need this, copy contrustor
}

AsteroidListItem::~AsteroidListItem() {
    //For the head Asteroid List Item , there is no asteroid point to in data, so this takes care of that
    //This check is redundant since delete is defined for nullptrs (defined to do nothing)
    //if(this->data != nullptr){
        delete this->data;
    //}
    
}

AsteroidList::AsteroidList(){
}

AsteroidList::AsteroidList(const AsteroidList& src){
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
    this->operator =(src);
}

AsteroidList::~AsteroidList() {
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
    this->clear();
}

void AsteroidList::pushFront(Asteroid e) {
    //set the head to a new asteroidlistitem, put the old head to oldFront
    AsteroidListItem* oldFront = this->head.setNext(new AsteroidListItem(e));
    //set next of the new front to the old front
    (this->head.getNext())->setNext(oldFront);
    return;
}

Asteroid& AsteroidList::front() {
    //This could be catastrophic if it was used on an empty list, but we don't need to worry about that case
    return ( (this->head.getNext()) -> getData() );
    //return *(Asteroid*)nullptr; not sure why its *(Asteroid*), is this to typecast?
}

const Asteroid& AsteroidList::front() const {
    return ( (this->head.getNext()) -> getData() );
    //return *(const Asteroid*)nullptr; dont need this, if list empty, head would already have nullptr
}

bool AsteroidList::isEmpty() const {
	if(this->head.getNext() != nullptr){
            return false;
        }
        return true;
}

int AsteroidList::size() const {
    const AsteroidListItem* next = this->head.getNext();
    int size=0;
    //This loop cycles until the end of the list, counting each node
    while(next!=nullptr){
        size++;
        next = next->getNext();
        //Im not sure if this line will work... reassigning a const variable seems weird, but i think
        //the const protects the pointed to info, not the actual pointer so it may be fine
    }
    return size;
}

AsteroidListItem* AsteroidList::beforeBegin() {
	return (&(this->head));
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	return (&(this->head));
}

AsteroidListItem* AsteroidList::begin() {
    return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
	return head.getNext();
}

AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem* temp = &head;
    while(temp->getNext() != nullptr){
        temp=temp->getNext();
    }
    return temp;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    const AsteroidListItem* temp = &head;
    while(temp->getNext() != nullptr){
        temp=temp->getNext();
    }
    return temp;
}

AsteroidListItem* AsteroidList::end() {
        //whether your list is empty or its full of nodes, it will always be nullptr terminating
        //this could traverse the whole list, but that would just be a waste of computing power
	return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
	return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    //store old next, insert new item in next, set next of new item to old next
    AsteroidListItem* temp = prev->getNext();
    prev->setNext(new AsteroidListItem(e));
    ( prev->getNext() )->setNext(temp);
    return (prev->getNext());
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    
    const AsteroidListItem* othersNext = others.head.getNext();
    AsteroidListItem* prevInsert = prev;
    
    //temp = old next node
    //toBeInserted = new next node (copied from 'others' list)
    //prevInsert = the last node inserted into the list
    //othersNext = node on 'others' which is next to be copied over
    while(othersNext!=nullptr){
        AsteroidListItem* temp = prevInsert->getNext();
        AsteroidListItem* toBeInserted = new AsteroidListItem( othersNext->getData() );
        prevInsert->setNext( toBeInserted );
        toBeInserted->setNext(temp);
        prevInsert = toBeInserted;
        othersNext = othersNext->getNext();
    }
    
    return prevInsert;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    AsteroidListItem* next = prev->getNext();
    prev->setNext( next->getNext() );
    delete next;
    return prev->getNext();
}

void AsteroidList::clear() {
    while(this->head.getNext() != nullptr){
        eraseAfter(&(this->head));
    }
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    this->clear();
    this->insertAfter(&(this->head), src);
    return *(this);
}
