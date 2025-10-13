#pragma once

class IRenderer
{
public:
    virtual ~IRenderer() = default;
    virtual int Init() = 0;
    virtual void Render() = 0;
	virtual void Terminate() = 0;
	virtual bool ShouldClose() = 0;
	virtual std::string GetInfo() = 0;
};
