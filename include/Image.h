// This file was developed by Thomas Müller <thomas94@gmx.net>.
// It is published under the BSD 3-Clause License within the LICENSE file.

#pragma once

#include "../include/Channel.h"
#include "../include/GlTexture.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

TEV_NAMESPACE_BEGIN

class Image {
public:
    Image(const std::string& filename, const std::string& channelSelector);

    const std::string& filename() const {
        return mFilename;
    }

    const std::string& channelSelector() const {
        return mChannelSelector;
    }

    const std::string& name() const {
        return mName;
    }

    std::string shortName() const;

    bool hasChannel(const std::string& channelName) const {
        return mChannels.count(channelName) != 0;
    }

    const Channel* channel(const std::string& channelName) const {
        if (hasChannel(channelName)) {
            return &mChannels.at(channelName);
        } else {
            return nullptr;
        }
    }

    const GlTexture* texture(const std::vector<std::string>& channelNames);

    std::vector<std::string> channelsInLayer(std::string layerName) const;

    const Eigen::Vector2i& size() const {
        return mSize;
    }

    const std::vector<std::string>& layers() const {
        return mLayers;
    }

    std::string toString() const;

private:
    void readStbi();
    void readExr();

    std::string mFilename;
    std::string mChannelSelector;

    std::string mName;
    Eigen::Vector2i mSize;

    size_t mNumChannels;
    std::map<std::string, Channel> mChannels;
    std::map<std::string, GlTexture> mTextures;

    std::vector<std::string> mLayers;
};

std::shared_ptr<Image> tryLoadImage(std::string filename, std::string channelSelector);

TEV_NAMESPACE_END
