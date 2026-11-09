// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.85462111;
  double density_weight = 0.33596354;
  double prefix_weight = 0.10721221;
  double neighborhood_weight = 0.25215680;
  double late_weight = 0.25626594;
  double critical_weight = 0.30732992;
  unsigned budget = 24;
  unsigned neighborhood = 5;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
