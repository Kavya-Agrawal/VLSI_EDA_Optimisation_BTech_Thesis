// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 1.24407033;
  double density_weight = 0.42241474;
  double prefix_weight = 0.35279649;
  double neighborhood_weight = 0.34078050;
  double late_weight = 0.13359486;
  double critical_weight = 0.31181882;
  unsigned budget = 16;
  unsigned neighborhood = 16;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
