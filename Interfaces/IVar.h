#ifndef _IVAR_H_
#define _IVAR_H_

class IVar
{
public:
    
    /// Virtual destructor method.
    virtual ~IVar( void ) { };
    
    /// Virtual accessor to return the variable's name.
    virtual const char* GetName( void ) = 0;
    
    /// Virtual accessor to return the datatype of variable.
    virtual const int GetType( void ) = 0;
    
    /// Virtual accessor to return the variable's integer value.
    virtual const int GetValueInt( void ) = 0;
    
    /// Virtual accessor to return the variable's float value.
    virtual const float GetValueFloat( void ) = 0;
    
    /// Virtual accessor to return the variable's boolean value.
    virtual const bool GetValueBool( void ) = 0;
    
    /// Virtual accessor to set the variable's integer value.
    virtual void SetValueInt( int iValue ) = 0;
        
    /// Virtual accessor to set the variable's float value.
    virtual void SetValueFloat( float fValue ) = 0;
    
    /// Virtual accessor to set variable's boolean value.
    virtual void SetValueBool( bool bValue ) = 0;
};

#endif // _IVAR_H_
