class DoublyLinkedListNode {
public:
    int key;
    int value;
    DoublyLinkedListNode *prev, *next;
    
    DoublyLinkedListNode() {
        key = value = 0;
        prev = next = NULL;
    }
    
    DoublyLinkedListNode(int key, int value) {
        this->key = key;
        this->value = value;
        prev = next = NULL;
    }
    
    void removeBindings() {
        this->prev = NULL;
        this->next = NULL;
    }

    ~DoublyLinkedListNode() {
    	if(prev != NULL) delete prev;
    	if(next != NULL) delete next;
    }
};

class DoublyLinkedList {
public:
    DoublyLinkedListNode *head, *tail;
    
    DoublyLinkedList() {
        head = tail = NULL;    
    }

    ~DoublyLinkedList() {
    	if(head != NULL) delete head;
    	if(tail != NULL) delete tail;
    }
    
    void setHeadTo(DoublyLinkedListNode *node) {
        // if the node itself is a head.
        if(head == node) {
            return;
        }
        
        // if the list is empty
        if(head == NULL) {
            head = node;
            tail = node;
            return;
        }
        
        // the list has only one node
        if(head == tail) {
            tail->prev = node;
            head = node;
            head->next = tail;
            return;
        }
        
        DoublyLinkedListNode *prev = node->prev;
        DoublyLinkedListNode *next = node->next;
        if(prev != NULL)
            prev->next = next;
        if(next != NULL)
            next->prev = prev;
        
        // if the node is at tail, then reset tail
        if(tail == node) {
            removeTail();
        }
        
        node->removeBindings();
        head->prev = node;
        node->next = head;
        head = node;
    }
    
    void removeTail() {
        // if list is empty
        if(tail == NULL) {
            return;
        }
        
        // if list has only one element
        if(tail == head) {
            head = NULL;
            tail = NULL;
            return;
        }
        
        tail = tail->prev;
        tail->next = NULL;
    }
};

class LRUCache {
private:
    DoublyLinkedList *listOfMostRecent;
    unordered_map<int, DoublyLinkedListNode*> cache;
    int capacity;
    int currentSize;
    
public:
    LRUCache(int capacity) {
        listOfMostRecent = new DoublyLinkedList();
        this->capacity = capacity;
        currentSize = 0;
    }

    ~LRUCache() {
    	if(listOfMostRecent != NULL) delete listOfMostRecent;
    }
    
    int get(int key) {
        // if key does not exist, then return -1
        // else return it's value
        if(cache[key] == NULL) {
            return -1;
        } else {
            // before return set this key to most recent 
            updateMostRecent(cache[key]);
            return cache[key]->value;
        }
    }
    
    void put(int key, int value) {
        // if the key does not exist, then add the key
        // else modidy the key
        if(cache[key] == NULL) {
            if(currentSize >= capacity) {
                evictLeastRecent(); 
            } else {
                currentSize += 1;
            }
            cache[key] = new DoublyLinkedListNode(key, value);
        } else {
            replaceKey(key, value);
        }
        
        // After adding or modifying, the node needs to be set to most recent
        updateMostRecent(cache[key]);
    }
    
    int getMostRecent() {
        // if list is empty
        if(listOfMostRecent->head == NULL) return -1;
        
        // else return most recent key
        return listOfMostRecent->head->key;
    }
    
private:
    void replaceKey(int key, int value) {
        cache[key]->value = value;
    }
    
    void evictLeastRecent() {
        int keyToRemove = listOfMostRecent->tail->key;
        listOfMostRecent->removeTail();
        cache[keyToRemove] = NULL; 
    }
    
    void updateMostRecent(DoublyLinkedListNode *node) {
        listOfMostRecent->setHeadTo(node);
    }
};