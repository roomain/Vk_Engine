#pragma once
/***********************************************
* @headerfile RHISerializable.h
* @date 27 / 03 / 2024
* @author Roomain
************************************************/

class RHISerializer;
class RHIDeserializer;

// interface for serializable object
class RHISerializable
{
public:
	virtual void serialize(RHISerializer& a_serializer) = 0;
	virtual void deserialize(RHIDeserializer& a_deserializer) = 0;
};
