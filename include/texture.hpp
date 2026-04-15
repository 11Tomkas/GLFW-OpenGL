#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture
{
    public:
        Texture();
        Texture(const Texture&) = delete;
        Texture(Texture&&) = delete;
        ~Texture();
        Texture& operator=(const Texture&) = delete;
        Texture& operator=(Texture&&) = delete;

        void bind(unsigned int target) const;
        void unbind(unsigned int target) const;
        void image2D(unsigned int target, int level, int internalFormat, int border, unsigned int format, unsigned int type, const char* fileName) const;
        void generateMipmap(unsigned int target);
    private:
        unsigned int m_name;
};

#endif