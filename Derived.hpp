class Derived : public Base
{       
    public:
        void Function1Impl()
        {
            std::cout << "Derived::Function1Impl()" << std::endl;
        }

        void Function2Impl()
        {
            std::cout << "Derived::Function2Impl()" << std::endl;
        }

        Derived()
        {  
            auto ptr = GetVPtr();
            SetVTablePointer(new VTable);
            TypeInfo tobjD;
            tobjD.CurrentClassName = "Derived";
            tobjD.BaseClassName = "Base";
            auto derived_ptr = GetVPtr();
            uint index = 1;
            for (auto i : ptr->GetFunctions()) {
                derived_ptr->AddFunction(index++, i.second);
            }

           
            std::vector<std::pair<int, std::string>> fvfcopy = find_virtual_functions("Base.hpp");
            
            GetVTablePointer()->SetTypeInfo(tobjD);//like index 0

            for (int i = 0; i < fvfcopy.size(); i++)
            {
                if (fvfcopy[i].second == "Function1Impl" && findFunction("Derived.hpp", "Function1Impl")) 
                {
                    GetVTablePointer()->AddFunction(fvfcopy[i].first, [this](){ Function1Impl(); });
                }

                else if (fvfcopy[i].second == "Function2Impl" && findFunction("Derived.hpp", "Function2Impl"))
                {
                    GetVTablePointer()->AddFunction(fvfcopy[i].first, [this](){ Function2Impl(); });
                }

                else if (fvfcopy[i].second == "~Base") {
                    GetVTablePointer()->AddFunction(3, [this](){ 
                        baseDestructState = false;
                        this->~Derived(); 
                    });
                }
                

            }

        }

        ~Derived() {
            derivedDestructState = true;
            std::cout << __PRETTY_FUNCTION__ << std::endl;
        }

};
