//Object.h                                                                                                                    

#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <sstream>
#include <iomanip>

#include "Type.h"
#include "Exception.h"

namespace NNet
{
        class Object
        {
        public:
                Object(Object* pParent = 0);
                virtual ~Object();

        void setParent(Object*);
                Object* getParent();

                bool is(const std::string& rAttributeName) const;
                void unset(const std::string& rAttributeName);
                void set(const std::string& rAttributeName, tAttribute);
                void set(const std::string& rAttributeName, tFloat);
                void set(const std::string& rAttributeName, const std::string&);
                void setAttribute(const std::string& rAttributeName, tAttribute);
                void setFloat(const std::string& rAttributeName, tFloat);
                void setString(const std::string& rAttributeName, const std::string&);
                tAttribute          get(const std::string& rAttributeName) const;
                tAttribute          getAttribute(const std::string& rAttributeName) const;
                tFloat              getFloat(const std::string& rAttributeName) const;
                const std::string&  getString(const std::string& rAttributeName) const;
        tAttribute operator[](const std::string& rAttributeName) const;

                const std::string stat() const;

        protected:
                Object* pParent;
                mutable std::map<std::string, tAttribute> Attributes;
        };

}; //namespace NNet

#endif
