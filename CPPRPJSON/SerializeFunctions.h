#pragma once

#include "../CPPRP/data/ReplayFileData.h"
#include "../CPPRP/data/NetworkData.h"
#include <cstdint>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
//#define RAPIDJSON_SIMD 1
#define RAPIDJSON_HAS_STDSTRING 1
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
namespace CPPRP
{
	namespace JSON
	{

		template<typename Writer, typename T>
		static inline const void Serialize(Writer& writer, const T& item)
		{
			//std::stringstream ss;
			//ss << "unsupported " << typeid(T).name();
			//std::string o = ss.str();
			//printf("%s\n", o.c_str());
			//assert(1 == 2);
			writer.String("");// (o.c_str(), o.size());
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const uint64_t& item)
		{
			char tmp[21], buf[21];

			char *tempPos = tmp;
			uint64_t q = item;
			do {
				*tempPos++ = "0123456789"[ q % 10 ];
				q /= 10;
			} while ( q );

			char *bufPos = buf;
			while(tempPos != tmp)
			{
				*bufPos++ = *--tempPos;
			}
			*bufPos = '\0';
			writer.String(buf);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const int64_t& item)
		{
			//Unoptimized since I don't think this is called much
			const std::string str = std::to_string(item);
			writer.String(str.c_str());
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const uint8_t& item)
		{
			writer.Uint(item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const char& item)
		{
			writer.Int((int)item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const float& item)
		{
			writer.Double(item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const std::string& item)
		{
			writer.String(item);
		}


		template<typename Writer>
		static inline const void Serialize(Writer& writer, const uint16_t& item)
		{
			writer.Uint(item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const uint32_t& item)
		{
			writer.Uint(item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const int8_t& item)
		{
			writer.Int(item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const int16_t& item)
		{
			writer.Int(item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const int32_t& item)
		{
			writer.Int(item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const bool& item)
		{
			writer.Bool(item);
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const Vector3& item)
		{
			/*char data[42] = "{\"X\":00000.00, \"Y\":00000.00, \"Z\":00000.00";

			int xabs = ((item.x < 0 ? -item.x : item.x) + 0.5f) * 100;
			data[5] = item.x < 0 ? '-' : ' ';
			data[6] = 48 + (xabs) / 100000;
			data[7] = 48 + (xabs % 100000) / 10000;
			data[8] = 48 + (xabs % 10000) / 1000;
			data[9] = 48 + (xabs % 1000) / 100;
			data[11] = 48 + (xabs % 100) / 10;
			data[12] = 48 + (xabs % 10) / 1;

			int yabs = ((item.y < 0 ? -item.y : item.y) + 0.5f) * 100;
			data[19] = item.y < 0 ? '-' : ' ';
			data[20] = 48 + (yabs) / 100000;
			data[21] = 48 + (yabs % 100000) / 10000;
			data[22] = 48 + (yabs % 10000) / 1000;
			data[23] = 48 + (yabs % 1000) / 100;
			data[25] = 48 + (yabs % 100) / 10;
			data[26] = 48 + (yabs % 10) / 1;


			int zabs = ((item.z < 0 ? -item.z : item.z) + 0.5f) * 100;
			data[33] = item.z < 0 ? '-' : ' ';
			data[34] = 48 + (zabs) / 100000;
			data[35] = 48 + (zabs % 100000) / 10000;
			data[36] = 48 + (zabs % 10000) / 1000;
			data[37] = 48 + (zabs % 1000) / 100;
			data[39] = 48 + (zabs % 100) / 10;
			data[40] = 48 + (zabs % 10) / 1;

			data[41] = '}';
			writer.RawValue(data, 42, rapidjson::kObjectType);*/
			writer.StartObject();
			writer.Key("X");
			Serialize<Writer>(writer, item.x);
			writer.Key("Y");
			Serialize<Writer>(writer, item.y);
			writer.Key("Z");
			Serialize<Writer>(writer, item.z);
			writer.EndObject();
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const Vector3I& item)
		{
			writer.StartObject();
			writer.Key("X");
			Serialize<Writer>(writer, item.x);
			writer.Key("Y");
			Serialize<Writer>(writer, item.y);
			writer.Key("Z");
			Serialize<Writer>(writer, item.z);
			writer.EndObject();
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const struct Quat& item)
		{
			writer.StartObject();
			writer.Key("X");
			Serialize<Writer>(writer, item.x);
			writer.Key("Y");
			Serialize<Writer>(writer, item.y);
			writer.Key("Z");
			Serialize<Writer>(writer, item.z);
			writer.Key("W");
			Serialize<Writer>(writer, item.w);
			writer.EndObject();
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const Rotator& item)
		{
			writer.StartObject();
			writer.Key("Pitch");
			Serialize<Writer>(writer, item.pitch);
			writer.Key("Yaw");
			Serialize<Writer>(writer, item.yaw);
			writer.Key("Roll");
			Serialize<Writer>(writer, item.roll);
			writer.EndObject();
		}

		template<typename Writer, typename T>
		static inline const void Serialize(Writer& writer, const std::vector<T>& item) {
			writer.StartArray();
			const size_t size = item.size();
			for (size_t i = 0; i < size; ++i)
			{
				Serialize(writer, item.at(i));
			}
			writer.EndArray();
		}

		template<typename Writer>
		static inline const void Serialize(Writer& writer, const std::shared_ptr<CPPRP::UniqueId>& item)
		{
			writer.StartObject();
			writer.Key("Platform");
			Serialize<Writer>(writer, item->platform);
			writer.Key("SplitscreenID");
			Serialize<Writer>(writer, item->splitscreenID);
			writer.Key("UniqueID");
			if (std::shared_ptr<CPPRP::SteamID> steamId = std::dynamic_pointer_cast<CPPRP::SteamID>(item); steamId)
			{
				Serialize<Writer>(writer, steamId->steamID);
				//writer.Uint64(steamId->steamID);
			}
			else if (std::shared_ptr<CPPRP::XBoxID> xboxId = std::dynamic_pointer_cast<CPPRP::XBoxID>(item); xboxId)
			{
				Serialize<Writer>(writer, xboxId->xboxID);
			}
			else if (std::shared_ptr<CPPRP::SwitchID> switchId = std::dynamic_pointer_cast<CPPRP::SwitchID>(item); switchId)
			{
				writer.StartArray();
				Serialize<Writer>(writer, switchId->a);
				Serialize<Writer>(writer, switchId->b);
				Serialize<Writer>(writer, switchId->c);
				Serialize<Writer>(writer, switchId->d);
				writer.EndArray();
			}
			else if (std::shared_ptr<CPPRP::PS4ID> ps4Id = std::dynamic_pointer_cast<CPPRP::PS4ID>(item); ps4Id)
			{
				Serialize<Writer>(writer, ps4Id->psId);
			}
			else if (std::shared_ptr<CPPRP::PsyNetID> psynetId = std::dynamic_pointer_cast<CPPRP::PsyNetID>(item); psynetId)
			{
				writer.StartArray();
				Serialize<Writer>(writer, psynetId->a);
				Serialize<Writer>(writer, psynetId->b);
				Serialize<Writer>(writer, psynetId->c);
				Serialize<Writer>(writer, psynetId->d);
				writer.EndArray();
			}
			else
			{
				Serialize<Writer>(writer, 1337);
			}
			writer.EndObject();
		}
		#include "GeneratedSerializeFunctions.h"
		
		template<typename Writer>
		class Serializer
		{
			public:
			
			typedef std::function<void(Writer&, std::shared_ptr<Engine::Actor>&)> writerFunc;
			std::unordered_map<std::string, writerFunc> writerFuncMap;
			std::vector<writerFunc> writerFuncs;

			template<typename T>
			inline void RegisterSerializer(const std::string& str, T callback)
			{
				writerFuncMap[str] = callback;
			}

			Serializer()
			{
#define fulln(namesp, classn, propname) xstr(namesp)"."xstr(classn)":"xstr(propname)
#define GAMEFIELD(namesp, classn, propname, nameoftype) \
	RegisterSerializer(fulln(namesp, classn, propname), [](Writer& writer, std::shared_ptr<Engine::Actor>& struc) { writer.Key(fulln(namesp, classn, propname)); Serialize<Writer>(writer, std::static_pointer_cast<CPPRP::namesp::classn>(struc)->propname); })

#include "../CPPRP/generated/GameClassMacros.h"
#undef fulln
#undef GAMEFIELD
			}
	
		};
		
		
	};
};