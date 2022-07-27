#ifndef HW03_VEHICLEFACTORY_H
#define HW03_VEHICLEFACTORY_H
#include <map>
#include <memory>
#include <vector>
using defaultIDKeyType = std::string;

template <class manufacturedObj, typename classIDKey=defaultIDKeyType>
class VehicleFactory
{
    using BASE_CREATE_FN = std::shared_ptr<manufacturedObj> (*) (const std::string &par);
    using FN_REGISTRY = std::map<classIDKey, BASE_CREATE_FN>;
    FN_REGISTRY registry;
    VehicleFactory() = default;
public:
    VehicleFactory(const VehicleFactory&) = delete;
    VehicleFactory &operator=(const VehicleFactory&) = delete;
    static VehicleFactory &instance();
    void regCreateFn(const classIDKey &, BASE_CREATE_FN);
    std::shared_ptr<manufacturedObj> create(const classIDKey &className,
                                            const std::string &params) const;
};

//template <class manufacturedObj, typename classIDKey>
//VehicleFactory<manufacturedObj, classIDKey>::VehicleFactory()
//= default;

template <class manufacturedObj, typename classIDKey>
VehicleFactory<manufacturedObj, classIDKey> &VehicleFactory<manufacturedObj, classIDKey>::instance()
{
    static VehicleFactory theInstance;
    return theInstance;
}


template <class manufacturedObj, typename classIDKey>
void VehicleFactory<manufacturedObj, classIDKey>::regCreateFn(const classIDKey &clName, BASE_CREATE_FN func)
{
    registry[clName]=func;
}


template <class manufacturedObj, typename classIDKey>
std::shared_ptr<manufacturedObj> VehicleFactory<manufacturedObj, classIDKey>::create(const classIDKey &className, const std::string &params) const
{
    std::shared_ptr<manufacturedObj> ret(nullptr);
    typename FN_REGISTRY::const_iterator regEntry = registry.find(className);
    if (regEntry != registry.end()) {
        return (*regEntry).second(params);
    }
    return ret;
}

template <class ancestorType,
        class manufacturedObj,
        typename classIDKey=defaultIDKeyType>
class registerInFactory {
public:
    static std::shared_ptr<manufacturedObj> createInstance(const std::string &params)
    {
        return std::shared_ptr<manufacturedObj>(manufacturedObj::createInstance(params));
    }
    explicit registerInFactory(const classIDKey &id)
    {
        VehicleFactory<manufacturedObj>::instance().regCreateFn(id, createInstance);
    }
};


#endif //HW03_VEHICLEFACTORY_H
