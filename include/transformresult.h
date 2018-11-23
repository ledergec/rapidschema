//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_TRANSFORMRESULT_H
#define RAPIDJSON_TRANSFORMRESULT_H

#include <string>
#include <vector>

#include "failure.h"

namespace rapidoson {

    class TransformResult {
    public:
        TransformResult() {}

        TransformResult(const Failure & failure) {
            failures_.push_back(failure);
        }

        const std::vector<Failure>& GetFailures() const {
            return failures_;
        }

        void Append(const TransformResult& other) {
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

        bool Success() const {
            return failures_.empty();
        }

        static TransformResult TRUE() {
            static TransformResult result;
            return result;
        }
   private:
        std::vector<Failure> failures_;
    };

}  // rapidjson

#endif //RAPIDJSON_TRANSFORMRESULT_H
