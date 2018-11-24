//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_FAILURE_COLLECTION_H
#define RAPIDJSON_FAILURE_COLLECTION_H

#include <optional>
#include <string>
#include <vector>

#include "failure.h"

namespace rapidoson {

    class FailureCollection {
    public:
        FailureCollection() {}

        FailureCollection(const Failure & failure) {
            failures_.push_back(failure);
        }

        const std::vector<Failure>& GetFailures() const {
            return failures_;
        }

        void Append(const FailureCollection& other) {
            std::copy(other.GetFailures().begin(), other.GetFailures().end(), std::back_inserter(failures_));
        }

        void Append(const Failure& other) {
            failures_.push_back(other);
        }

        void AddPath(const std::string& path) {
            for (auto failure : failures_) {
                if (failure.path.empty()) {
                    failure.path = path;
                } else {
                    failure.path = path + "." + failure.path;
                }
            }
        }

    private:
        std::vector<Failure> failures_;
    };

    static std::optional<FailureCollection> operator + (std::optional<FailureCollection> lhs,
                                                        std::optional<FailureCollection> rhs) {
        if (lhs.has_value()) {
            if (rhs.has_value()) {
                lhs.value().Append(rhs.value());
                return lhs;
            } else {
                return lhs;
            }
        } else {
            return rhs;
        }
    }
}  // rapidjson

#endif //RAPIDJSON_FAILURE_COLLECTION_H
