// listad.h
#if !defined(LIST_AD_NUME) || !defined(LIST_AD_ELEMENT)
#error "LIST and ELEMENT must be defined before the header is included."
#endif

typedef struct
{
    LIST_AD_ELEMENT *first;
    LIST_AD_ELEMENT *last;
} LIST_AD_NUME;

#ifndef LIST_AD_FN
// aceste macrouri sunt definite doar daca listad.h nu a mai fost inclus anterior
#define LIST_AD_FNAUX(NUME, OPERATIE) NUME##_##OPERATIE
#define LIST_AD_FN(NUME, OPERATIE) LIST_AD_FNAUX(NUME, OPERATIE)
#endif

void LIST_AD_FN(LIST_AD_NUME, initialize)(LIST_AD_NUME *list)
{
    list->first = list->last = NULL;
}

void LIST_AD_FN(LIST_AD_NUME, add)(LIST_AD_NUME *list, LIST_AD_ELEMENT *element)
{
    element->previous = list->last;
    if (list->last)
    {
        list->last->next = element;
    }
    else
    {
        list->first = element;
    }
    list->last = element;
    element->next = NULL;
}

void LIST_AD_FN(LIST_AD_NUME, delete)(LIST_AD_NUME *list, LIST_AD_ELEMENT *element)
{
    if (element->previous)
    {
        element->previous->next = element->next;
    }
    else
    {
        list->first = element->next;
    }
    if (element->next)
    {
        element->next->previous = element->previous;
    }
    else
    {
        list->last = element->previous;
    }
    free(element);
}

void LIST_AD_FN(LIST_AD_NUME, freeMemory)(LIST_AD_NUME *list)
{
    LIST_AD_ELEMENT *element, *next;
    for (element = list->first; element; element = next)
    {
        next = element->next;
        free(element);
    }
    LIST_AD_FN(LIST_AD_NUME, initialize)
    (list);
}

void LIST_AD_FN(LIST_AD_NUME, addElementBeforePosition)(LIST_AD_NUME *list, LIST_AD_ELEMENT *position, LIST_AD_ELEMENT *element)
{
    LIST_AD_ELEMENT *exists, *iterator;

    for (iterator = list->first; iterator; iterator = iterator->next)
        if (!strcmp(iterator->text, position->text))
        {
            exists = iterator;
            break;
        }
        else
            exists = NULL;

    if (exists)
    {
        element->next = exists;
        element->previous = exists->previous;
        exists->previous->next = element;
    }
    else
        LIST_AD_FN(LIST_AD_NUME, add)
    (list, element);
}

// the definitions must be deleted for using the same header more times in the same source file
#undef LIST_AD_NUME
#undef LIST_AD_ELEMENT