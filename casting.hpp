template<typename Derived, typename Base>
Derived* my_dynamic_cast(Base* base)
{
    if (base->GetVPtr()->GetTypeInfo().CurrentClassName == Derived().GetVPtr()->GetTypeInfo().BaseClassName) // or "Base" (rhs of ==)
    {
        return static_cast<Derived*>(base);
    }
    return nullptr;
    
}