//
// Created by Christopher Vaughn on 10/24/25.
//

#ifndef CIRCULARTEMPLATEDLIST_LINKEDLIST_H
#define CIRCULARTEMPLATEDLIST_LINKEDLIST_H

#include "Media.h"
#include <iostream>

template <typename T>
struct Node {
    T data;
    Node<T>* next;

    // Constructor initializes data and pointer
    Node(T media) : data(media), next(nullptr) {}
};

// === 5. Hard-coded LinkedList Class (Singly, Non-Circular) ===
// This list is only capable of managing Media* objects (Song*, Podcast*, etc.) and is forward-only.
template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    // Constructor: Initializes an empty list
    LinkedList() : head(nullptr) {}

    // Destructor: Cleans up all nodes and the Media objects they point to.
    ~LinkedList() {
        if (head == nullptr) return;
        Node<T>* current = head;
        Node<T>* next_node = nullptr;

        do{
            next_node = current->next;
            delete current->data;
            delete current;
            current = next_node;
        } while (current != head);

       
        head = nullptr; // Ensure head is reset
        std::cout << "\n[Playlist cleanup complete. All memory deallocated.]" << std::endl;
    }

    // Insertion: Adds a new Media pointer to the end of the list.
    void insert(T newMedia) {
        Node<T>* newNode = new Node<T>(newMedia);

        if (head == nullptr) {
            // Case 1: List is empty. New node becomes the head.
            head = newNode;
            newNode->next = head;
        } else {
            // Case 2: Traverse to the end and link the new node.
            Node<T>* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newNode;
            newNode->next = head;
        }
    }

    // Traversal: Displays all media items in the list.
    void displayList() const {
        if (head == nullptr) {
            std::cout << "\n[Playlist is empty.]" << std::endl;
            return;
        }

        std::cout << "\n--- Current Playlist ---" << std::endl;
        Node<T>* current = head;
        int index = 1;
        do {
            // Polymorphism in action: calls the specific toString() method for Song or Podcast
            std::cout << index++ << ". " << current->data->toString() << std::endl;
            current = current->next;
        } while (current != head);
        std::cout << "------------------------" << std::endl;
    }

    // Simple play method for demonstration (students will expand this later)
    void playCurrent() const {
        if (head != nullptr) {
            head->data->play(); // Calls the virtual play() method
        } else {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
        }
    }
};
void playNext(Node<Media*>*& currentSong) const {
        if (currentSong != nullptr) {
            currentSong = currentSong->next;
            currentSong->data->play();
        }

}
#endif //CIRCULARTEMPLATEDLIST_LINKEDLIST_H