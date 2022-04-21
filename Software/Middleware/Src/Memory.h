//*******************************************************************
/*!
\file   Memory.h
\author Thomas Breuer
\date
\brief  Variablen dauerhaft (persistent) speichern
*/

//*******************************************************************
#ifndef _MEMORY_H
#define _MEMORY_H

//*******************************************************************
/*! \brief Persistenter Speicher
*/
class Memory
{
  public:
    //*******************************************************************
    /*! \brief Eintrag im persistenten Speicher

        Als Speicher wird der Flash verwendet. Da dieser nur blockweise
        überschrieben werden kann, werden alle Speicherinhalte im RAM
        zwischengespeichert und erst mit der Methode Memory::store() in
        den Flash geschrieben. Da die Anzahl der Löschvorgänge technisch
        beschränkt ist, sollte Memory::store() nur verwendet werden,
        wenn dies wirklich notwendig ist.
    */
    class Item
    {
      private:
        //---------------------------------------------------------------
        Item   *next;
        int     value;
        DWORD   addr;

      public:
        //---------------------------------------------------------------
        /*! Erzeugt einen Speichereintrag

            Um eine Variable dauerhaft zu speichern, muss sie als Memory::Item
            deklariert werden. Optional kann eine Adresse vergeben werden, es
            wird aber nicht geprüft, ob diese Adresse belegt ist. Alternativ
            (ohne Adressangabe) wird die Adresse automatisch vergeben.

            Alte, nicht mehr benötigte Speicherinhalte werden <b>nicht</b>
            automatisch gelöscht.
            Der komplette Speicher lässt sich mit dem
            ORB-Monitor löschen, der Default-Wert ist dann -1.

            Um alle Speichereinträge endgültig zu speichern, muss die Methode
            Memory::store() aufgerufen werden.
            \param addr Adresse des Speichereintrags (optional)
        */
        Item( DWORD addr = (DWORD)(-1) )
        {
          next = NULL;
          Memory::addItem( this, addr );
        }

        //---------------------------------------------------------------
        /*! Weist einen Wert dem Speichereintrag zu. Die endgültige
        Speicherung erfolgt jedoch erst mit der Methode Memory::store().
        */
        void operator=( int x )
        {
          value = x;
        }

        //---------------------------------------------------------------
        /*! Gibt den Inhalt des Speichereintrags zurück

            \return Inhalt
        */
        operator int()
        {
          return( value );
        }

      friend class Memory;
    };

  private:
    //---------------------------------------------------------------
    static Memory::Item *first;

    //---------------------------------------------------------------
    static void addItem( Memory::Item *item, DWORD addr );

  public:
    //---------------------------------------------------------------
    /*! Setzt die Verwaltung der Speichereinträge zurück.
    Der Flash-Speicher selbst wird <b>nicht</b> gelöscht.
    */
    static void clean( void )
    {
      first = 0;
    }

    //---------------------------------------------------------------
    /*! Schreibt alle Speichereinträge endgültig in den persistenten
        Speicher

        Aufgrund der gegrenzten Lebensdauer des Flash-Speichers
        (max 10000 Löschzyklen) sollte diese Methode nur aufgerufen
        werden, wenn dies unbedingt erforderlich ist.
    */
    static void store( void );

    friend class Memory::Item;
};

//*******************************************************************
Memory::Item *Memory::first = NULL;

//*******************************************************************
void Memory::addItem( Memory::Item *notiz, DWORD addrIn )
{
  unsigned int addr = 0;

  if( first )
  {
    Memory::Item *ptr = first;
    while( ptr )
    {
      addr += sizeof(int);

      if( ptr->next == NULL )
      {
        ptr->next = notiz;
        break;
      }
      ptr = ptr->next;
    }
  }
  else
  {
    first = notiz;
  }

  notiz->addr = ( addrIn != (DWORD)(-1) ) ? addrIn : addr;
  orbPtr->getMemory(notiz->addr, (unsigned char*)&notiz->value, sizeof(notiz->value) );
}

//*******************************************************************
void Memory::store( void )
{
  bool dirty = false;

  Memory::Item *ptr = first;

  while( ptr && !dirty)
  {
    int original = 0;
    orbPtr->getMemory( ptr->addr, (unsigned char*)&original, sizeof(ptr->value) );
    if( original != ptr->value )
    {
      dirty = true;
    }
    ptr = ptr->next;
  }

  if( dirty )
  {
    orbPtr->clearMemory();
  }

  ptr = first;

  while( ptr )
  {
    if( dirty )
    {
      orbPtr->setMemory( ptr->addr, (unsigned char*)&ptr->value, sizeof(ptr->value) );
    }
    orbPtr->getMemory( ptr->addr, (unsigned char*)&ptr->value, sizeof(ptr->value) );
    ptr = ptr->next;
  }
}

#endif
