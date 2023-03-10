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

// the definitions must be deleted for using the same header more times in the same source file
#undef LIST_AD_NUME
#undef LIST_AD_ELEMENT