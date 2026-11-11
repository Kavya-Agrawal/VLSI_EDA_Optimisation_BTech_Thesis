// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.21807774;
  double density_weight = 0.41207626;
  double prefix_weight = 0.40836609;
  double neighborhood_weight = 0.15441885;
  double late_weight = 0.03755505;
  double critical_weight = 0.06854889;
  unsigned budget = 16;
  unsigned neighborhood = 3;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
